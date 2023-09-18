import tiktoken

encoder = tiktoken.get_encoding('cl100k_base')
token = encoder.encode('你《好')
print(token)