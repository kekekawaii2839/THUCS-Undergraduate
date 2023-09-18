import json

def filter_jsonl(input_file, output_file):
    with open(output_file, 'w', encoding='utf-8') as output_f:
        with open(input_file, 'r', encoding='utf-8') as input_f:
            for line in input_f:
                json_data = json.loads(line.strip())
                likes_num = json_data.get('likes_num', 0)
                comments_num = json_data.get('comments_num', 0)
                comments = json_data.get('comments', {})
                tags = json_data.get('tags', [])

                if likes_num != 0 or comments_num != 0 or comments or tags:
                    output_f.write(line)

input_file = 'sorted.jsonl'    # 你的输入jsonl文件名
output_file = 'sorted_selected.jsonl'  # 输出文件名，保留满足条件的行

filter_jsonl(input_file, output_file)
