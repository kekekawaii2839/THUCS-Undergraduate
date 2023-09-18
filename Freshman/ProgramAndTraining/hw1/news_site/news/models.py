from django.db import models
from datetime import datetime

class News(models.Model):
    title = models.CharField(max_length=30)
    author = models.CharField(max_length=20)
    time = models.CharField(max_length=20)
    url = models.CharField(max_length=100)
    content = models.TextField()
    likes_num = models.IntegerField()
    comments_num = models.IntegerField()
    source = models.CharField(max_length=30, default='')

    def get_year_month(self):
        return datetime.strptime(self.time, '%Y-%m-%d %H:%M').strftime('%Y-%m')

class Comment(models.Model):
    news = models.ForeignKey(News, on_delete=models.CASCADE, default=None)
    user = models.CharField(max_length=20)
    time = models.CharField(max_length=20)
    content = models.TextField()

    class Meta:
        ordering = ['-time']

class Tag(models.Model):
    news = models.ForeignKey(News, on_delete=models.CASCADE, default=None)
    text = models.CharField(max_length=20)