from django.urls import path, include
import news.views as views

urlpatterns = [
    path('news/<int:id>', views.show_news),
    path('news/<int:id>/comment', views.comment),
    path('news/comment/delete/<int:comment_id>', views.delete_comment),
    path('news/<int:id>/like', views.like_news),
    path('list', views.news_list),
    path('', views.index),
    path('categories/', views.category_list),
    path('categories/<str:year_month>/', views.category_detail),
    path('search/', views.search),
    path('news/images/<str:filename>', views.get_image)
]