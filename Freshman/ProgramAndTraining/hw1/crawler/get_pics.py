import json
import os
import requests
from bs4 import BeautifulSoup
import uuid

if not os.path.exists('images'):
    os.mkdir('images')

with open('sorted_selected.jsonl', 'r', encoding='utf-8') as input_file, open('sorted_selected_pics.jsonl', 'w', encoding='utf-8') as output_file:
    for line in input_file:
        data = json.loads(line.strip())
        content = data.get('content', '')
        soup = BeautifulSoup(content, 'html.parser')

        img_tags = soup.find_all('img')
        for img_tag in img_tags:
            img_url = img_tag.get('src')
            if img_url:
                img_extension = os.path.splitext(img_url)[1]
                img_filename = os.path.join('images', f'{uuid.uuid4()}{img_extension}')
                f = False
                while not f:
                    try:
                        response = requests.get(img_url)
                        with open(img_filename, 'wb') as img_file:
                            img_file.write(response.content)
                        f = True
                    except:
                        #img_filename = ''
                        print(f'Error: {img_url}', data['title'])
                        #with open('error.log', 'a', encoding='utf-8') as error_file:
                        #    error_file.write(f'{img_url}\n')

                img_tag['src'] = img_filename
        data['content'] = str(soup)
        output_file.write(json.dumps(data, ensure_ascii=False) + '\n')