from private_openai_v2 import *
import json
import jsonlines

def g(question):
    answer = ''
    user_content = "请你回答下面这个问题，除了回答本身不需要输出其他任何内容。\n问题："+question+"\n\n你的回答："
    messages = [
        {"role": "system", "content": "你是一位研究金庸武侠小说的专家。"},
        {"role": "user", "content": user_content},
    ]
    while answer == '':
        try:
            result = Openai(messages, model='gpt-4', temperature=0.8)
            response = result['choices'][0]['message']['content']
            answer = response
        except Exception as e:
            print('error:', e)
            answer = ''
    return answer

with open('questions.jsonl', 'r', encoding='utf-8') as f:
    for line in f:
        data = json.loads(line)
        question = data['Question']
        print(question)
        data['Answer'] = g(question)
        print(data['Answer'])

        with jsonlines.open('result.jsonl', 'a') as haha:
            haha.write(data)
