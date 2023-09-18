import json

def remove_duplicates(input_file, output_file):
    seen_titles = set()

    with open(output_file, 'w', encoding='utf-8') as output_f:
        with open(input_file, 'r', encoding='utf-8') as input_f:
            for line in input_f:
                json_data = json.loads(line.strip())
                title = json_data.get('title')

                if title is not None and title not in seen_titles:
                    seen_titles.add(title)
                    output_f.write(line)

input_file = 'sorted_authorfix.jsonl'    # 你的输入jsonl文件名
output_file = 'sorted_filtered.jsonl'  # 输出文件名，保留没有重复title的行

remove_duplicates(input_file, output_file)
