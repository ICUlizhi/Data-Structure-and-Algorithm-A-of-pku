import os
import re

def extract_first_number(filename):
    """
    从文件名中提取第一个数字，如果没有数字，则返回一个较大的默认值。
    """
    match = re.search(r'\d+', filename)
    return int(match.group()) if match else float('inf')

def concatenate_md_files_by_number(directory):
    output_file = "note.md"
    md_files = [
        f for f in os.listdir(directory)
        if f.endswith(".md") and f != output_file
    ]

    # 按文件名中的第一个数字排序
    md_files.sort(key=extract_first_number)

    output_path = os.path.join(directory, output_file)
    
    with open(output_path, "w", encoding="utf-8") as outfile:
        for md_file in md_files:
            file_path = os.path.join(directory, md_file)
            with open(file_path, "r", encoding="utf-8") as infile:
                content = infile.read()
                outfile.write(content)
                outfile.write("\n___\n")  # 添加换行分隔符

    print(f"All .md files have been concatenated into {output_file}.")

# 示例调用
directory_path = "./"  # 替换为目标目录的路径
concatenate_md_files_by_number(directory_path)
