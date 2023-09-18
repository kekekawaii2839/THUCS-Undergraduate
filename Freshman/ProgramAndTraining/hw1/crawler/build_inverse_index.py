import jieba
import json
from bs4 import BeautifulSoup
import numpy as np
from collections import Counter, defaultdict
import re
import dill as pickle

term_newsid_pairs = []
news_length = []

class InvertedIndex:
    def __init__(self, newsid, tf=0):
        self.newsids = newsid # starts from 1
        self.tf = tf
    def __repr__(self):
        return f'<newsid: {self.newsids}, tf: {self.tf}>'

def ff(text):
    pattern = r"[\u4e00-\u9fff\w]+"
    return re.match(pattern, text) is not None

total_news = open('sorted_selected_pics.jsonl', 'r', encoding='utf-8').readlines().__len__()

with open('sorted_selected_pics.jsonl', 'r', encoding='utf-8') as f:
    for line_index, line in enumerate(f):
        data = json.loads(line)
        title = data['title']
        content = data['content']
        author = data['author']
        tags = data['tags']
        content = BeautifulSoup(content, 'html.parser')
        # delete all image_desc class
        for img_desc in content.find_all('div', class_='image_desc'):
            img_desc.decompose()
        # delete all news_video_name class
        for video_name in content.find_all('div', class_='news_video_name'):
            video_name.decompose()
        content = content.get_text()
        content = content.replace('\n', '').replace('\r', '').replace('\t', '').replace(' ', '')
        for tag in tags:
            tag =  tag[1:]
        title_terms = list(jieba.cut_for_search(title))
        content_terms = list(jieba.cut_for_search(content))
        author_terms = list(jieba.cut_for_search(author))

        terms = title_terms + content_terms + author_terms
        for tag in tags:
            terms.extend(list(jieba.cut_for_search(tag)))

        for term in terms:
            if ff(term[0]) == True:
                term_newsid_pairs.append((term, line_index+1))

term_newsid_pairs = sorted(term_newsid_pairs)
inverted_index = defaultdict(lambda: [InvertedIndex(0, 0)])

for term, newsid in term_newsid_pairs:
    news_list = inverted_index[term]
    if newsid != news_list[-1].newsids:
        inverted_index[term].append(InvertedIndex(newsid, 1))
    else:
        inverted_index[term][-1].tf += 1
inverted_index = dict(inverted_index)

for k, v in inverted_index.items():
    for news in v:
        news.tf *= np.log(total_news/len(inverted_index[k]))
#print(inverted_index)

fout = open('./inverted_index.pkl', 'wb')
pickle.dump(inverted_index, fout)
fout.close()