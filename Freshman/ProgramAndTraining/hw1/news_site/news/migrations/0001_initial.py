# Generated by Django 4.2.4 on 2023-08-28 11:06

from django.db import migrations, models
import django.db.models.deletion


class Migration(migrations.Migration):

    initial = True

    dependencies = []

    operations = [
        migrations.CreateModel(
            name="News",
            fields=[
                (
                    "id",
                    models.BigAutoField(
                        auto_created=True,
                        primary_key=True,
                        serialize=False,
                        verbose_name="ID",
                    ),
                ),
                ("title", models.CharField(max_length=30)),
                ("author", models.CharField(max_length=20)),
                ("time", models.CharField(max_length=20)),
                ("url", models.CharField(max_length=100)),
                ("content", models.TextField()),
                ("likes_num", models.IntegerField()),
                ("comments_num", models.IntegerField()),
                ("source", models.CharField(default="", max_length=30)),
            ],
        ),
        migrations.CreateModel(
            name="Tag",
            fields=[
                (
                    "id",
                    models.BigAutoField(
                        auto_created=True,
                        primary_key=True,
                        serialize=False,
                        verbose_name="ID",
                    ),
                ),
                ("text", models.CharField(max_length=20)),
                (
                    "news",
                    models.ForeignKey(
                        default=None,
                        on_delete=django.db.models.deletion.CASCADE,
                        to="news.news",
                    ),
                ),
            ],
        ),
        migrations.CreateModel(
            name="Comment",
            fields=[
                (
                    "id",
                    models.BigAutoField(
                        auto_created=True,
                        primary_key=True,
                        serialize=False,
                        verbose_name="ID",
                    ),
                ),
                ("user", models.CharField(max_length=20)),
                ("time", models.CharField(max_length=20)),
                ("content", models.TextField()),
                (
                    "news",
                    models.ForeignKey(
                        default=None,
                        on_delete=django.db.models.deletion.CASCADE,
                        to="news.news",
                    ),
                ),
            ],
            options={
                "ordering": ["-time"],
            },
        ),
    ]