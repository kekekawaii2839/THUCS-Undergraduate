import re
import time
from bs4 import BeautifulSoup
import jsonlines
from selenium import webdriver
from selenium.webdriver.common.by import By

options = webdriver.ChromeOptions()
user_agent = 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/116.0.0.0 Safari/537.36 Edg/116.0.1938.54'
options.add_argument(f'user-agent={user_agent}')
options.add_argument('--ignore-ssl-errors')
options.add_argument('--ignore-certificate-errors')
options.add_argument('--disable-gpu')
options.add_argument('--ignore-certificate-errors-spki-list')
options.add_argument('--ignore-urlfetcher-cert-requests')
driver = webdriver.Chrome(options=options)

def remove_html_tags(text):
    soup = BeautifulSoup(text, 'html.parser')
    return soup.get_text()

def scrape(url, cookie_str=None):
    try:
        global driver
        driver.get(url)
        if driver.current_url != url:
            print("invaild url:", url)
            return {}
        time.sleep(0.5)
        js_code = 'window.scrollBy(0, document.body.scrollHeight)'
        driver.execute_script(script=js_code)
        time.sleep(1)
        
        page_source = driver.page_source
        soup = BeautifulSoup(page_source, 'html.parser')

        title = soup.find('h1', class_='index_title__B8mhI').text
        print(title)
        author_items = soup.find_all('div', class_='index_left__LfzyH')
        author = author_items[0].find('div').text
        
        meta_items = soup.find_all('div', class_='ant-space-item')
        ttime = meta_items[0].find('span').text

        if ttime == '':
            pattern = re.compile(r'\d{4}-\d{2}-\d{2} \d{2}:\d{2}')
            ttime = pattern.match(author)[0]
            author = author[len(ttime)+1:]
        
        print(author)
        print(ttime)

        content = soup.find('div', class_='index_cententWrap__Jv8jK')
        # print(content)

        side_items = soup.find('ul', class_='index_ul__FuyOn')
        # print(side_items)
        likes_num = side_items.find('div', class_='praiseNum index_num__lvDnF', recursive=True)
        likes_num = int(likes_num.text) if likes_num and likes_num.text!='' else 0
        print("likes_num =", likes_num)
        comments_num = side_items.find('div', class_='index_number__S7ufV', recursive=True)
        comments_num = int(comments_num.text) if comments_num and comments_num.text!='' else 0
        print("comments_num =", comments_num)

        comment_authors = soup.find_all('a', class_='index_inherit__A1ImK index_author__nkMZt')
        comments = soup.find_all('div', class_='index_content__g237N')
        comment_sum = {}
        for i in range(len(comment_authors)):
            print(comment_authors[i].text, ":", comments[i].text)
            comment_sum[comment_authors[i].text] = comments[i].text
        
        tag_items = soup.find_all('span', class_='index_tag__21BlE commonCursor')
        tags = []
        if len(tag_items) > 0:
            tags = []
            for tag in tag_items:
                tags.append(tag.text)
            print(tags)

        result = {
            "url": url,
            "title": title,
            "author": author,
            "time": ttime,
            "content": str(content),
            "likes_num": likes_num,
            "comments_num": comments_num,
            "comments": comment_sum,
            "tags": tags
        }

        return result

    except Exception as e:
        print("error:", e)
        return {}

for i in range(10005250, 24370250, 1000):
    url_prefix = 'https://www.thepaper.cn/newsDetail_forward_'
    url = url_prefix + "%.8d" % i
    print("scraping:", url)
    res = scrape(url)
    if res == {}:
        continue
    with jsonlines.open('test.jsonl', 'a') as writer:
        writer.write(res)