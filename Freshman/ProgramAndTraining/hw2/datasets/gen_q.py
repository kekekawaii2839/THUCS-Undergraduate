from private_openai_v2 import *
import jsonlines

# titles = ['书剑恩仇录', '侠客行', '倚天屠龙记', '天龙八部', '射雕英雄传', '白马啸西风', '碧血剑', '神雕侠侣', '笑傲江湖', '越女剑', '连城诀', '雪山飞狐', '飞狐外传', '鸳鸯刀', '鹿鼎记']
titles = ['天龙八部', '射雕英雄传', '神雕侠侣']

for title in titles:
    user_content = f"""你好！你能帮我生成60个关于《{title}》的问题吗？有以下四个方面及其例子供你参考：
    1. 人物介绍
        请你介绍一下《{title}》的主角。
    2. 情节
        请你讲一下{title}中有名的比武的情节。
    3. 人物关系
        小龙女和杨过之间是什么关系？他们之间发生了什么故事？
    4. 其他
        《{title}》讲了什么故事？

    请你指明问题对应的书名，按照以下格式生成，并且不要输出额外的任何内容：
    00. xxx
    01. xxx
    02. xxx
    03. xxx
    ...
    58. xxx
    59. xxx"""

    messages = [
        {"role": "system", "content": "你是一位研究金庸武侠小说的专家。"},
        {"role": "user", "content": user_content},
    ]
    response = ''
    while response == '':
        try:
            result = Openai(messages, model="gpt-4", temperature=0.9, max_tokens=2000)
            response = result['choices'][0]['message']['content']
            print(response)
        except Exception as e:
            print(result)
            response = ''

    # parse response
    questions = response.split('\n')
    questions = [q[4:] for q in questions if q != '']

    # write to jsonl
    with jsonlines.open('questions.jsonl', mode='a') as writer:
        for q in questions:
            writer.write({'Question': q, 'Answer': ''})