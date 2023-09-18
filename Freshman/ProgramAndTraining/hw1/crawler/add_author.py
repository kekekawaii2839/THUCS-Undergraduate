import json
import jsonlines
import time
from bs4 import BeautifulSoup
from selenium import webdriver

options = webdriver.ChromeOptions()
user_agent = 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/116.0.0.0 Safari/537.36 Edg/116.0.1938.54'
options.add_argument(f'user-agent={user_agent}')
#options.add_argument("--proxy-server=http://127.0.0.1:7890")
options.add_argument('--ignore-ssl-errors')
options.add_argument('--ignore-certificate-errors') #忽略CERT证书错误
options.add_argument('--disable-gpu')
options.add_argument('--ignore-certificate-errors-spki-list')
options.add_argument('--ignore-urlfetcher-cert-requests')
driver = webdriver.Chrome(options=options)  # 需要提前安装 Chrome 浏览器和对应版本的 ChromeDriver

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
        
        page_source = driver.page_source
        soup = BeautifulSoup(page_source, 'html.parser')
        
        author_items = soup.find('span', class_='index_name__ID4kk')
        author = author_items.text
        print(author)

        return author

    except Exception as e:
        print("发生错误:", e)
        return {}

with open('sorted.jsonl', 'r', encoding='utf-8') as f:
    for line_index, line in enumerate(f):
        data = json.loads(line)
        if data["author"].endswith("来源：澎湃新闻·澎湃号·政务") \
                or data["author"].endswith("来源：澎湃新闻·澎湃号·媒体") \
                or data["author"].endswith("来源：澎湃新闻·澎湃号·湃客"):
            data["source"] = data["author"]
            print(data["source"])
            data["author"] = scrape(data["url"])
            print(data["url"])
            print()
        else:
            data["source"] = ""
        with jsonlines.open('sorted_authorfix.jsonl', mode='a') as writer:
            writer.write(data)