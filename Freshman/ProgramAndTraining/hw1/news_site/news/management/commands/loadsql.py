import json
from news.models import *
from django.core.management.base import BaseCommand

class Command(BaseCommand):
    help = 'Load data from jsonl file to database'
    
    def add_arguments(self, parser):
        parser.add_argument('filename', type=str)

    def handle(self, *args, **options):
        filename = options['filename']
        with open(filename, 'r', encoding='utf-8') as f:
            for line_index, line in enumerate(f):
                data = json.loads(line.strip())
                url = data.get('url')
                title = data.get('title')
                author = data.get('author')
                time = data.get('time')
                content = data.get('content')
                likes_num = data.get('likes_num')
                comments_num = data.get('comments_num')
                comments = data.get('comments')
                comments = dict(comments)
                tags = data.get('tags')
                source = data.get('source')
    
                print(line_index, title)
    
                news = News(title=title, author=author, time=time, url=url, content=content, likes_num=likes_num, comments_num=comments_num, source=source)
                news.save()
    
                for user, content in comments.items():
                    comment = Comment(news=news, user=user, time=time, content=content)
                    comment.save()
    
                for tag in tags:
                    text = tag
                    print(text)
                    tag = Tag(news=news, text=text)
                    tag.save()