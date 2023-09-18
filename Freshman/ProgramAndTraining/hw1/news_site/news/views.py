from django.shortcuts import render, get_object_or_404, redirect
from .models import *
from django.template import loader
from django.http import HttpResponse, HttpResponseRedirect
from django.views.decorators.http import require_POST
import time
import random
from django.core.paginator import Paginator
from django.db.models import Q
from collections import defaultdict, Counter
import dill as pickle
import jieba
import numpy as np
import re

# -----------------for news detail-----------------
def show_news(request, id):
    news = News.objects.get(id=id)
    template = loader.get_template('news/news_detail.html')
    context = {
        'news': news,
        'comments': Comment.objects.filter(news=news),
        'tags': Tag.objects.filter(news=news),
        'category': news.time.split()[0][:7],
    }
    return HttpResponse(template.render(context, request))

@require_POST
def comment(request, id):
    news = News.objects.get(id=id)
    user=request.POST['username']
    content=request.POST['content']
    if user and content:
        Comment.objects.create(
            news=news, user=user,
            content=content,
            time=time.strftime("%Y-%m-%d %H:%M", time.localtime())
        )

        news.comments_num += 1
        news.save()
    return HttpResponseRedirect('/news/' + str(news.id))

@require_POST
def delete_comment(request, comment_id):
    comment = get_object_or_404(Comment, id=comment_id)
    news_id = comment.news.id
    news = News.objects.get(id=news_id)
    news.comments_num -= 1
    news.save()
    comment.delete()
    return redirect('/news/' + str(news_id))

@require_POST
def like_news(request, id):
    news = News.objects.get(id=id)
    print(request.POST.get('isLiked'))
    if request.POST.get('isLiked') == 'true':
        news.likes_num += 1
    else:
        news.likes_num -= 1
    news.save()
    return redirect('/news/' + str(id))

# -----------------for news list-----------------
def news_list(request):
    news_list = News.objects.all().order_by('-time')
    paginator = Paginator(news_list, 5)

    page_number = request.GET.get('page')
    page_obj = paginator.get_page(page_number)

    context = {
        'page_obj': page_obj
    }
    return render(request, 'news/news_list.html', context)

# -----------------for mainpage-----------------
categories = []
for news in News.objects.all().order_by('-time'):
    year_month = news.time.split()[0][:7]
    if year_month not in categories:
        categories.append(year_month)

def index(request):
    random_news = random.sample(list(News.objects.all()), min(20, News.objects.count()))
    global categories
    context = {
        'random_news': random_news,
        'categories': categories,
    }
    return render(request, 'index.html', context)

# -----------------for category-----------------
def category_list(request):
    news_list = News.objects.all()

    year_month_counts = defaultdict(int)

    for news in news_list:
        year_month = news.time.split()[0][:7]
        year_month_counts[year_month] += 1
    
    year_month_counts = dict(sorted(year_month_counts.items(), reverse=True))

    context = {
        'year_month_counts': year_month_counts.items(),
    }
    return render(request, 'category_list.html', context)

def category_detail(request, year_month):
    news_list = News.objects.filter(time__startswith=year_month).order_by('-time')
    paginator = Paginator(news_list, 10)

    page_number = request.GET.get('page')
    page_obj = paginator.get_page(page_number)

    context = {
        'category': year_month,
        'page_obj': page_obj
    }
    return render(request, 'category_detail.html', context)

# -----------------for search-----------------
class InvertedIndex:
    def __init__(self, newsid, tf=0):
        self.newsids = newsid # starts from 1
        self.tf = tf
    def __repr__(self):
        return f'<newsid: {self.newsids}, tf: {self.tf}>'

with open('./news/inverted_index.pkl', 'rb') as fin:
    inverted_index = pickle.load(fin)
jieba.initialize()

def ff(text):
    pattern = r"[\u4e00-\u9fff\w]+"
    return re.match(pattern, text) is not None

def query(inverted_index, query_term):
    querys = set(filter(ff, jieba.cut_for_search(query_term)))
    news_list = {}
    for query_term in querys:
        if query_term in inverted_index:
            news_list[query_term] = inverted_index[query_term][1:] # 删去开头的空index类对象
    # 筛选出所有query_term都出现的新闻
    news_flatten_list = [x for v in news_list.values() for x in v]
    news_index = [x.newsids for x in news_flatten_list]
    counter = Counter(news_index)
    news_index = [x for x in counter if counter[x] == len(querys)]
    """news_all_list = [x for x in news_flatten_list if x.newsids in news_index]
    query_result = {}
    for news in news_all_list:
        if news.newsids in query_result:
            query_result[news.newsids] += news.tf
        else:
            query_result[news.newsids] = news.tf
    query_result = sorted(query_result.items(), key=lambda x: x[1], reverse=True)
    query_result = [InvertedIndex(x[0], x[1]) for x in query_result]
    # 对相关性做一定程度上的过滤 以保证结果质量
    query_result = query_result[:max(50, len(query_result)//2)]
    return query_result"""
    return news_index

def search(request):
    keyword = request.GET.get('keyword')
    sort_method = request.GET.getlist('sort')[0]
    category = request.GET.getlist('category')
    time_start = time.time()
    q_object = Q()
    for year_month in category:
        q_object = q_object | Q(time__startswith=year_month)
    if keyword is None or keyword == '':
        news_list = News.objects.all()
    else:
        query_result = query(inverted_index, keyword)
        # query_result = [x.newsids for x in query_result]
        news_list = News.objects.filter(id__in=query_result)
    if sort_method == 'time':
        news_list = news_list.filter(q_object)
        news_list = news_list.order_by('-time')
    elif sort_method == 'popularity':
        news_list = news_list.filter(q_object)
        news_list = sorted(news_list, key=lambda x: x.likes_num, reverse=True)
    
    time_end = time.time()
    time_comsumed = time_end - time_start
    print("time_comsumed =", time_comsumed)

    paginator = Paginator(news_list, 10)
    page_number = request.GET.get('page')
    print("page_number =", page_number)
    page_obj = paginator.get_page(page_number)

    link_prefix = 'keyword=' + keyword + '&sort=' + sort_method
    for i in range(len(category)):
        link_prefix += '&category=' + category[i]
    
    global categories
    context = {
        'link_prefix': link_prefix,
        'page_obj': page_obj,
        'time_comsumed': time_comsumed,
        'result_num': len(news_list),
        'selected_categories': category,
        'categories': categories,
        'keyword': keyword,
        'sort_method': sort_method,
    }
    return render(request, 'search.html', context)

# -----------------for image-----------------
def get_image(request, filename):
    with open('./news/images/' + filename, 'rb') as f:
        image_data = f.read()
    return HttpResponse(image_data, content_type="image/png")