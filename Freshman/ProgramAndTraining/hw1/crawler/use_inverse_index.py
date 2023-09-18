import dill as pickle
import json
from bs4 import BeautifulSoup

class InvertedIndex:
    def __init__(self, newsid, tf=0):
        self.newsids = newsid # starts from 1
        self.tf = tf
    def __repr__(self):
        return f'<newsid: {self.newsids}, tf: {self.tf}>'

with open('./inverted_index.pkl', 'rb') as fin:
    inverted_index = pickle.load(fin)

def query(inverted_index, filename, query_term):
    news_list = inverted_index[query_term][1:] # 删去开头的Posting(-1, 0)
    news_list = sorted(news_list, key=lambda x: x.tf, reverse=True)
    print(news_list)
    collections = {}
    with open(filename, 'r', encoding='utf-8') as f:
        for line_index, line in enumerate(f):
            collections[line_index+1] = json.loads(line)['title']
    results = [collections[news.newsids] for news in news_list]
    return results

def output_results(query, query_func=query, inverted_index=inverted_index):
    print('query: %s, results: %s' % (query, query_func(inverted_index, 'sorted_selected.jsonl', query)))

output_results('美国')