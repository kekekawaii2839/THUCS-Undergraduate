with open('sorted.jsonl', 'r', encoding='utf-8') as f:
    lines = [line.strip() for line in f]
    lines.sort()
with open('sorted2.jsonl', 'w', encoding='utf-8') as f:
    for line in lines:
        f.write(line + '\n')