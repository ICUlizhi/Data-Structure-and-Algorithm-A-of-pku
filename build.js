const fs = require('fs');
const path = require('path');

// 简单的Markdown转HTML转换器
function convertMarkdownToHtml(content) {
  // 标题
  content = content.replace(/^### (.*$)/gim, '<h3>$1</h3>');
  content = content.replace(/^## (.*$)/gim, '<h2>$1</h2>');
  content = content.replace(/^# (.*$)/gim, '<h1>$1</h1>');
  
  // 粗体和斜体
  content = content.replace(/\*\*(.*)\*\*/gim, '<strong>$1</strong>');
  content = content.replace(/\*(.*)\*/gim, '<em>$1</em>');
  
  // 代码块
  content = content.replace(/```([\s\S]*?)```/gim, '<pre><code>$1</code></pre>');
  content = content.replace(/`(.*?)`/gim, '<code>$1</code>');
  
  // 链接
  content = content.replace(/\[([^\]]+)\]\(([^\)]+)\)/gim, '<a href="$2">$1</a>');
  
  // 图片
  content = content.replace(/!\[([^\]]*)\]\(([^\)]+)\)/gim, '<img alt="$1" src="$2" />');
  
  // 列表
  content = content.replace(/^\* (.*$)/gim, '<li>$1</li>');
  content = content.replace(/^- (.*$)/gim, '<li>$1</li>');
  
  // 段落
  content = content.replace(/\n\n/gim, '</p><p>');
  content = '<p>' + content + '</p>';
  
  // 清理空段落
  content = content.replace(/<p><\/p>/g, '');
  
  return content;
}

function createHTML(title, content) {
  return `<!DOCTYPE html>
<html lang="zh-CN">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>${title}</title>
    <style>
        body {
            font-family: -apple-system, BlinkMacSystemFont, 'Segoe UI', Helvetica, Arial, sans-serif;
            line-height: 1.6;
            color: #24292e;
            background-color: #fff;
            max-width: 900px;
            margin: 0 auto;
            padding: 20px;
        }
        h1, h2, h3, h4, h5, h6 {
            margin-top: 24px;
            margin-bottom: 16px;
            font-weight: 600;
            line-height: 1.25;
        }
        h1 { font-size: 2em; border-bottom: 1px solid #eaecef; padding-bottom: 0.3em; }
        h2 { font-size: 1.5em; border-bottom: 1px solid #eaecef; padding-bottom: 0.3em; }
        h3 { font-size: 1.25em; }
        code {
            padding: 0.2em 0.4em;
            margin: 0;
            font-size: 85%;
            background-color: rgba(27,31,35,0.05);
            border-radius: 3px;
            font-family: 'SFMono-Regular', Consolas, 'Liberation Mono', Menlo, monospace;
        }
        pre {
            padding: 16px;
            overflow: auto;
            font-size: 85%;
            line-height: 1.45;
            background-color: #f6f8fa;
            border-radius: 6px;
        }
        pre code {
            padding: 0;
            background-color: transparent;
        }
        blockquote {
            padding: 0 1em;
            color: #6a737d;
            border-left: 0.25em solid #dfe2e5;
            margin: 16px 0;
        }
        table {
            border-spacing: 0;
            border-collapse: collapse;
            margin: 16px 0;
        }
        table th, table td {
            padding: 6px 13px;
            border: 1px solid #dfe2e5;
        }
        table tr:nth-child(2n) {
            background-color: #f6f8fa;
        }
        a {
            color: #0366d6;
            text-decoration: none;
        }
        a:hover {
            text-decoration: underline;
        }
        img {
            max-width: 100%;
            box-sizing: content-box;
        }
        ul {
            padding-left: 2em;
        }
        li {
            margin: 0.25em 0;
        }
    </style>
</head>
<body>
    ${content}
</body>
</html>`;
}

function convertFile(inputPath, outputPath) {
  try {
    const content = fs.readFileSync(inputPath, 'utf-8');
    const html = convertMarkdownToHtml(content);
    const title = path.basename(inputPath, '.md');
    const htmlContent = createHTML(title, html);
    fs.writeFileSync(outputPath, htmlContent);
    console.log(`Converted: ${inputPath} -> ${outputPath}`);
  } catch (err) {
    console.error(`Error converting ${inputPath}:`, err.message);
  }
}

function convertDirectory(dir, outputBase) {
  if (!fs.existsSync(dir)) return;
  
  const items = fs.readdirSync(dir);
  
  items.forEach(item => {
    const inputPath = path.join(dir, item);
    const stat = fs.statSync(inputPath);
    
    if (stat.isDirectory() && !item.startsWith('.') && item !== 'node_modules') {
      const outputDir = path.join(outputBase, item);
      if (!fs.existsSync(outputDir)) {
        fs.mkdirSync(outputDir, { recursive: true });
      }
      convertDirectory(inputPath, outputDir);
    } else if (stat.isFile() && item.endsWith('.md')) {
      const outputFile = path.join(outputBase, item.replace('.md', '.html'));
      convertFile(inputPath, outputFile);
    }
  });
}

function createIndex() {
  const indexContent = `
    <h1>数据结构与算法 A - PKU</h1>
    <p>欢迎来到北京大学数据结构与算法A课程资料库</p>
    <h2>目录</h2>
    <ul>
      <li><a href="README.html">项目介绍</a></li>
    </ul>
    <p>使用上方的导航或查看转换后的HTML文件。</p>
  `;
  
  const indexHTML = createHTML('数据结构与算法 A - PKU', indexContent);
  fs.writeFileSync('docs/index.html', indexHTML);
  console.log('Created: docs/index.html');
}

// 开始转换
console.log('Starting Markdown to HTML conversion...');

// 创建docs目录
if (!fs.existsSync('docs')) {
  fs.mkdirSync('docs', { recursive: true });
}

// 转换根目录的README.md
if (fs.existsSync('README.md')) {
  convertFile('README.md', 'docs/README.html');
}

// 转换notes目录
['notes-上机', 'notes-理论-期中前', 'notes-理论-期中后'].forEach(dir => {
  if (fs.existsSync(dir)) {
    const outputDir = path.join('docs', dir);
    if (!fs.existsSync(outputDir)) {
      fs.mkdirSync(outputDir, { recursive: true });
    }
    convertDirectory(dir, outputDir);
  }
});

// 创建索引页
createIndex();

console.log('Conversion completed!');
console.log('Open docs/index.html in your browser to view the site.');