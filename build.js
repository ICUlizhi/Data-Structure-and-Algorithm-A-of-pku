const fs = require('fs');
const path = require('path');

// 高级Markdown转HTML转换器，支持更多语法
function convertMarkdownToHtml(content) {
  // 代码块（优先处理，避免与其他规则冲突）
  content = content.replace(/```(\w+)?\n([\s\S]*?)```/g, (match, lang, code) => {
    const language = lang || 'plaintext';
    return `<div class="code-block"><div class="code-header">${language}</div><pre><code class="language-${language}">${code.trim()}</code></pre></div>`;
  });
  
  // 行内代码
  content = content.replace(/`([^`]+)`/g, '<code class="inline-code">$1</code>');
  
  // 标题
  content = content.replace(/^#### (.*$)/gim, '<h4>$1</h4>');
  content = content.replace(/^### (.*$)/gim, '<h3>$1</h3>');
  content = content.replace(/^## (.*$)/gim, '<h2>$1</h2>');
  content = content.replace(/^# (.*$)/gim, '<h1>$1</h1>');
  
  // 粗体和斜体
  content = content.replace(/\*\*(.*?)\*\*/g, '<strong>$1</strong>');
  content = content.replace(/\*(.*?)\*/g, '<em>$1</em>');
  
  // 链接
  content = content.replace(/\[([^\]]+)\]\(([^\)]+)\)/g, '<a href="$2" class="link" target="_blank">$1</a>');
  
  // 图片
  content = content.replace(/!\[([^\]]*)\]\(([^\)]+)\)/g, '<img alt="$1" src="$2" class="content-image" />');
  
  // 引用块
  content = content.replace(/^> (.*$)/gim, '<blockquote class="quote">$1</blockquote>');
  
  // 列表
  content = content.replace(/^\* (.*$)/gim, '<li class="list-item">$1</li>');
  content = content.replace(/^- (.*$)/gim, '<li class="list-item">$1</li>');
  content = content.replace(/^\d+\. (.*$)/gim, '<li class="list-item">$1</li>');
  
  // 复选框
  content = content.replace(/^- \[x\] (.*$)/gim, '<li class="task-item completed"><input type="checkbox" checked disabled> $1</li>');
  content = content.replace(/^- \[ \] (.*$)/gim, '<li class="task-item"><input type="checkbox" disabled> $1</li>');
  
  // 表格
  content = content.replace(/\n\|(.+)\|\n\|(.+)\|\n((?:\n\|(.+)\|)*)/g, (match, header, separator, rows) => {
    const headers = header.split('|').map(h => h.trim()).filter(h => h);
    const headerHtml = '<thead><tr>' + headers.map(h => `<th>${h}</th>`).join('') + '</tr></thead>';
    
    const rowMatches = rows.match(/\n\|(.+)\|/g) || [];
    const rowHtml = rowMatches.map(row => {
      const cells = row.replace(/\n\|/, '').replace(/\|$/, '').split('|').map(c => c.trim());
      return '<tr>' + cells.map(c => `<td>${c}</td>`).join('') + '</tr>';
    }).join('');
    
    return `<div class="table-wrapper"><table class="data-table">${headerHtml}<tbody>${rowHtml}</tbody></table></div>`;
  });
  
  // 分割线
  content = content.replace(/^---$/gim, '<hr class="divider">');
  content = content.replace(/^\*\*\*$/gim, '<hr class="divider">');
  
  // 警告框
  content = content.replace(/^> \[!NOTE\]\n> (.*(?:\n> .*)*)/gim, '<div class="alert alert-note"><strong>注意：</strong><br>$1</div>');
  content = content.replace(/^> \[!WARNING\]\n> (.*(?:\n> .*)*)/gim, '<div class="alert alert-warning"><strong>警告：</strong><br>$1</div>');
  content = content.replace(/^> \[!TIP\]\n> (.*(?:\n> .*)*)/gim, '<div class="alert alert-tip"><strong>提示：</strong><br>$1</div>');
  
  // 段落
  content = content.replace(/\n\n/g, '</p><p>');
  content = '<p>' + content + '</p>';
  
  // 清理空段落和多余的p标签
  content = content.replace(/<p><\/p>/g, '');
  content = content.replace(/<p>(<div[^>]*>)/g, '$1');
  content = content.replace(/(<\/div>)<\/p>/g, '$1');
  
  // 修复列表
  content = content.replace(/<p>(<li[^>]*>.*<\/li>)<\/p>/g, '$1');
  content = content.replace(/(<li[^>]*>.*<\/li>)\s*(?=<li[^>]*>)/g, '$1');
  
  // 包装列表
  content = content.replace(/(<li[^>]*>.*<\/li>)/g, '<ul class="content-list">$1</ul>');
  
  return content;
}

function createHTML(title, content, pageType = 'default') {
  const navigation = `
    <nav class="navbar">
      <div class="nav-container">
        <div class="nav-brand">
          <a href="index.html" class="brand-link">
            <span class="brand-icon">🎓</span>
            <span class="brand-text">数据结构与算法 A</span>
          </a>
        </div>
        <div class="nav-menu">
          <div class="nav-item dropdown">
            <a href="#" class="nav-link">📚 课程资源</a>
            <div class="dropdown-content">
              <a href="https://dsa.openjudge.cn/" target="_blank" class="dropdown-link">
                <span class="link-icon">🎯</span>课程OJ
              </a>
              <a href="https://www.icourse163.org/course/PKU-1002534001" target="_blank" class="dropdown-link">
                <span class="link-icon">📖</span>MOOC课程
              </a>
              <a href="http://dsalgo.openjudge.cn/" target="_blank" class="dropdown-link">
                <span class="link-icon">💻</span>MOOC OJ
              </a>
              <a href="https://pkuhub.cn/course/1830" target="_blank" class="dropdown-link">
                <span class="link-icon">🏫</span>PKUHUB课程页
              </a>
            </div>
          </div>
          <div class="nav-item dropdown">
            <a href="#" class="nav-link">📝 学习资料</a>
            <div class="dropdown-content">
              <a href="notes-上机.html" class="dropdown-link">
                <span class="link-icon">⚙️</span>上机笔记
              </a>
              <a href="notes-理论-期中前.html" class="dropdown-link">
                <span class="link-icon">📊</span>理论笔记(期中前)
              </a>
              <a href="notes-理论-期中后.html" class="dropdown-link">
                <span class="link-icon">📈</span>理论笔记(期中后)
              </a>
            </div>
          </div>
          <div class="nav-item dropdown">
            <a href="#" class="nav-link">🔧 助教工具</a>
            <div class="dropdown-content">
              <a href="ta-dashboard.html" class="dropdown-link">
                <span class="link-icon">📊</span>助教工作台
              </a>
              <a href="#" class="dropdown-link">
                <span class="link-icon">📋</span>作业管理
              </a>
              <a href="#" class="dropdown-link">
                <span class="link-icon">📊</span>成绩统计
              </a>
              <a href="#" class="dropdown-link">
                <span class="link-icon">💬</span>答疑记录
              </a>
              <a href="#" class="dropdown-link">
                <span class="link-icon">📅</span>课程安排
              </a>
            </div>
          </div>
          <div class="nav-item dropdown">
            <a href="#" class="nav-link">📚 往年资源</a>
            <div class="dropdown-content">
              <a href="往年资料/" class="dropdown-link">
                <span class="link-icon">📁</span>往年资料
              </a>
              <a href="往年资料/" class="dropdown-link">
                <span class="link-icon">📝</span>往年题解
              </a>
            </div>
          </div>
          <div class="nav-item">
            <a href="README.html" class="nav-link">ℹ️ 关于</a>
          </div>
        </div>
        <div class="nav-toggle">
          <span></span>
          <span></span>
          <span></span>
        </div>
      </div>
    </nav>
  `;

  const footer = `
    <footer class="footer">
      <div class="footer-content">
        <div class="footer-section">
          <h3>课程信息</h3>
          <p>北京大学数据结构与算法A</p>
          <p>2025年秋季学期</p>
        </div>
        <div class="footer-section">
          <h3>快速链接</h3>
          <ul class="footer-links">
            <li><a href="https://dsa.openjudge.cn/">课程OJ</a></li>
            <li><a href="https://pkuhub.cn/course/1830">PKUHUB</a></li>
          </ul>
        </div>
        <div class="footer-section">
          <h3>联系方式</h3>
          <p>助教：ICUlizhi</p>
          <p>邮箱：iculizhi@gmail.com</p>
        </div>
      </div>
      <div class="footer-bottom">
        <p>&copy; 2025 数据结构与算法A - PKU. All rights reserved.</p>
      </div>
    </footer>
  `;

  return `<!DOCTYPE html>
<html lang="zh-CN">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>${title}</title>
    <style>
      ${getEnhancedStyles()}
    </style>
</head>
<body>
    ${navigation}
    
    <main class="main-content">
        <div class="container">
            ${pageType === 'home' ? getHomePageContent() : ''}
            <div class="content-wrapper">
                ${content}
            </div>
        </div>
    </main>
    
    ${footer}
    
    <script>
      ${getInteractiveScript()}
    </script>
</body>
</html>`;
}

function getEnhancedStyles() {
  return `
    /* Enhanced Modern Styles for DSA Course Website */

    /* CSS Variables for consistent theming */
    :root {
      --primary-color: #667eea;
      --primary-dark: #764ba2;
      --secondary-color: #f093fb;
      --accent-color: #4facfe;
      --success-color: #48bb78;
      --warning-color: #ed8936;
      --error-color: #f56565;
      --info-color: #4299e1;
      
      --bg-gradient: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
      --card-gradient: linear-gradient(135deg, rgba(255,255,255,0.95) 0%, rgba(255,255,255,0.9) 100%);
      --glass-effect: rgba(255, 255, 255, 0.25);
      --glass-border: rgba(255, 255, 255, 0.18);
      
      --text-primary: #2d3748;
      --text-secondary: #4a5568;
      --text-muted: #718096;
      
      --shadow-light: 0 4px 6px rgba(0, 0, 0, 0.05);
      --shadow-medium: 0 10px 15px rgba(0, 0, 0, 0.1);
      --shadow-heavy: 0 25px 50px rgba(0, 0, 0, 0.15);
      --shadow-glow: 0 0 20px rgba(102, 126, 234, 0.3);
      
      --border-radius: 12px;
      --border-radius-lg: 20px;
      --transition: all 0.3s cubic-bezier(0.4, 0, 0.2, 1);
    }

    /* Advanced Animations */
    @keyframes fadeInUp {
      from {
        opacity: 0;
        transform: translateY(30px);
      }
      to {
        opacity: 1;
        transform: translateY(0);
      }
    }

    @keyframes fadeInLeft {
      from {
        opacity: 0;
        transform: translateX(-30px);
      }
      to {
        opacity: 1;
        transform: translateX(0);
      }
    }

    @keyframes float {
      0%, 100% { transform: translateY(0px); }
      50% { transform: translateY(-10px); }
    }

    @keyframes pulse {
      0%, 100% { transform: scale(1); }
      50% { transform: scale(1.05); }
    }

    @keyframes shimmer {
      0% { background-position: -200% 0; }
      100% { background-position: 200% 0; }
    }

    * {
      margin: 0;
      padding: 0;
      box-sizing: border-box;
    }

    body {
      font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
      line-height: 1.6;
      color: var(--text-primary);
      background: var(--bg-gradient);
      min-height: 100vh;
    }

    .navbar {
      background: rgba(255, 255, 255, 0.95);
      backdrop-filter: blur(10px);
      box-shadow: 0 4px 20px rgba(0, 0, 0, 0.1);
      position: sticky;
      top: 0;
      z-index: 1000;
      transition: all 0.3s ease;
    }

    .nav-container {
      max-width: 1200px;
      margin: 0 auto;
      display: flex;
      justify-content: space-between;
      align-items: center;
      padding: 0 2rem;
      height: 70px;
    }

    .nav-brand {
      font-size: 1.5rem;
      font-weight: bold;
      color: #4a5568;
    }

    .brand-link {
      text-decoration: none;
      color: inherit;
      display: flex;
      align-items: center;
      gap: 0.5rem;
    }

    .brand-icon {
      font-size: 1.8rem;
    }

    .nav-menu {
      display: flex;
      gap: 2rem;
      align-items: center;
    }

    .nav-item {
      position: relative;
    }

    .nav-link {
      text-decoration: none;
      color: #4a5568;
      font-weight: 500;
      padding: 0.5rem 1rem;
      border-radius: 8px;
      transition: all 0.3s ease;
      display: flex;
      align-items: center;
      gap: 0.5rem;
    }

    .nav-link:hover {
      background: linear-gradient(135deg, #667eea, #764ba2);
      color: white;
      transform: translateY(-2px);
      box-shadow: 0 4px 15px rgba(102, 126, 234, 0.4);
    }

    .dropdown-content {
      position: absolute;
      top: 100%;
      left: 0;
      background: white;
      min-width: 220px;
      box-shadow: 0 10px 30px rgba(0, 0, 0, 0.15);
      border-radius: 12px;
      opacity: 0;
      visibility: hidden;
      transform: translateY(-10px);
      transition: all 0.3s ease;
      padding: 0.5rem 0;
      z-index: 1001;
    }

    .nav-item:hover .dropdown-content {
      opacity: 1;
      visibility: visible;
      transform: translateY(0);
    }

    .dropdown-link {
      display: flex;
      align-items: center;
      gap: 0.8rem;
      padding: 0.8rem 1.2rem;
      text-decoration: none;
      color: #4a5568;
      transition: all 0.3s ease;
      font-size: 0.95rem;
    }

    .dropdown-link:hover {
      background: #f7fafc;
      color: #667eea;
      transform: translateX(5px);
    }

    .link-icon {
      font-size: 1.1rem;
      width: 20px;
      text-align: center;
    }

    .nav-toggle {
      display: none;
      flex-direction: column;
      cursor: pointer;
      gap: 4px;
    }

    .nav-toggle span {
      width: 25px;
      height: 3px;
      background: #4a5568;
      transition: all 0.3s ease;
    }

    .main-content {
      flex: 1;
      padding: 2rem 0;
    }

    .container {
      max-width: 1200px;
      margin: 0 auto;
      padding: 0 2rem;
    }

    .content-wrapper {
      background: rgba(255, 255, 255, 0.95);
      backdrop-filter: blur(10px);
      border-radius: 20px;
      padding: 3rem;
      margin: 2rem 0;
      box-shadow: 0 20px 40px rgba(0, 0, 0, 0.1);
      border: 1px solid rgba(255, 255, 255, 0.2);
    }

    h1, h2, h3, h4, h5, h6 {
      margin-bottom: 1.5rem;
      font-weight: 600;
      line-height: 1.3;
    }

    h1 { 
      font-size: 2.5rem; 
      background: linear-gradient(135deg, #667eea, #764ba2);
      -webkit-background-clip: text;
      -webkit-text-fill-color: transparent;
      background-clip: text;
      margin-bottom: 2rem;
      text-align: center;
    }

    h2 { 
      font-size: 2rem; 
      color: #2d3748;
      border-bottom: 3px solid #667eea;
      padding-bottom: 0.5rem;
      margin-top: 3rem;
    }

    h3 { 
      font-size: 1.5rem; 
      color: #4a5568;
      margin-top: 2rem;
    }

    p {
      margin-bottom: 1.5rem;
      color: #4a5568;
      font-size: 1.1rem;
      line-height: 1.8;
    }

    .link {
      color: #667eea;
      text-decoration: none;
      font-weight: 500;
      transition: all 0.3s ease;
      border-bottom: 2px solid transparent;
    }

    .link:hover {
      color: #764ba2;
      border-bottom-color: #667eea;
    }

    .inline-code {
      background: #f7fafc;
      color: #e53e3e;
      padding: 0.2rem 0.5rem;
      border-radius: 6px;
      font-family: 'SFMono-Regular', Consolas, 'Liberation Mono', Menlo, monospace;
      font-size: 0.9em;
      border: 1px solid #e2e8f0;
    }

    .code-block {
      background: #1a202c;
      border-radius: 12px;
      margin: 2rem 0;
      overflow: hidden;
      box-shadow: 0 10px 25px rgba(0, 0, 0, 0.3);
    }

    .code-header {
      background: #2d3748;
      color: #e2e8f0;
      padding: 0.8rem 1.2rem;
      font-size: 0.9rem;
      font-weight: 500;
      border-bottom: 1px solid #4a5568;
    }

    .code-block pre {
      margin: 0;
      padding: 1.5rem;
      background: transparent;
      color: #e2e8f0;
      font-size: 0.95rem;
      line-height: 1.6;
      overflow-x: auto;
    }

    .quote {
      border-left: 4px solid #667eea;
      background: #f7fafc;
      padding: 1.5rem;
      margin: 2rem 0;
      border-radius: 0 12px 12px 0;
      font-style: italic;
      color: #4a5568;
    }

    .content-list {
      list-style: none;
      padding: 0;
      margin: 1.5rem 0;
    }

    .list-item {
      padding: 0.8rem 0;
      border-bottom: 1px solid #e2e8f0;
      position: relative;
      padding-left: 2rem;
    }

    .list-item:before {
      content: "→";
      position: absolute;
      left: 0;
      color: #667eea;
      font-weight: bold;
    }

    .list-item:last-child {
      border-bottom: none;
    }

    .task-item {
      list-style: none;
      padding: 0.8rem 0;
      display: flex;
      align-items: center;
      gap: 0.8rem;
    }

    .task-item input[type="checkbox"] {
      width: 18px;
      height: 18px;
      accent-color: #667eea;
    }

    .task-item.completed {
      opacity: 0.7;
      text-decoration: line-through;
    }

    .table-wrapper {
      overflow-x: auto;
      margin: 2rem 0;
      border-radius: 12px;
      box-shadow: 0 4px 15px rgba(0, 0, 0, 0.1);
    }

    .data-table {
      width: 100%;
      border-collapse: collapse;
      background: white;
      border-radius: 12px;
      overflow: hidden;
    }

    .data-table th {
      background: linear-gradient(135deg, #667eea, #764ba2);
      color: white;
      padding: 1rem;
      text-align: left;
      font-weight: 600;
    }

    .data-table td {
      padding: 1rem;
      border-bottom: 1px solid #e2e8f0;
    }

    .data-table tr:hover {
      background: #f7fafc;
    }

    .alert {
      padding: 1.5rem;
      border-radius: 12px;
      margin: 2rem 0;
      border-left: 4px solid;
    }

    .alert-note {
      background: #ebf8ff;
      border-left-color: #3182ce;
      color: #2c5282;
    }

    .alert-warning {
      background: #fed7d7;
      border-left-color: #e53e3e;
      color: #742a2a;
    }

    .alert-tip {
      background: #f0fff4;
      border-left-color: #38a169;
      color: #22543d;
    }

    .divider {
      border: none;
      height: 2px;
      background: linear-gradient(90deg, #667eea, #764ba2);
      margin: 3rem 0;
      border-radius: 2px;
    }

    .content-image {
      max-width: 100%;
      height: auto;
      border-radius: 12px;
      box-shadow: 0 8px 25px rgba(0, 0, 0, 0.15);
      margin: 2rem 0;
    }

    .footer {
      background: rgba(26, 32, 44, 0.95);
      backdrop-filter: blur(10px);
      color: #e2e8f0;
      padding: 3rem 0 1rem;
      margin-top: 4rem;
    }

    .footer-content {
      max-width: 1200px;
      margin: 0 auto;
      padding: 0 2rem;
      display: grid;
      grid-template-columns: repeat(auto-fit, minmax(250px, 1fr));
      gap: 2rem;
    }

    .footer-section h3 {
      color: #667eea;
      margin-bottom: 1rem;
      font-size: 1.2rem;
    }

    .footer-links {
      list-style: none;
    }

    .footer-links a {
      color: #e2e8f0;
      text-decoration: none;
      transition: color 0.3s ease;
    }

    .footer-links a:hover {
      color: #667eea;
    }

    .footer-bottom {
      text-align: center;
      padding-top: 2rem;
      border-top: 1px solid #4a5568;
      margin-top: 2rem;
      color: #a0aec0;
    }

    @media (max-width: 768px) {
      .nav-container {
        padding: 0 1rem;
      }

      .nav-menu {
        position: fixed;
        top: 70px;
        left: -100%;
        width: 100%;
        height: calc(100vh - 70px);
        background: rgba(255, 255, 255, 0.95);
        backdrop-filter: blur(10px);
        flex-direction: column;
        justify-content: flex-start;
        align-items: flex-start;
        padding: 2rem;
        transition: left 0.3s ease;
        gap: 1rem;
      }

      .nav-menu.active {
        left: 0;
      }

      .nav-toggle {
        display: flex;
      }

      .dropdown-content {
        position: static;
        opacity: 1;
        visibility: visible;
        transform: none;
        box-shadow: none;
        background: transparent;
        padding-left: 1rem;
        margin-top: 0.5rem;
      }

      .content-wrapper {
        padding: 2rem;
        margin: 1rem;
      }

      h1 {
        font-size: 2rem;
      }

      h2 {
        font-size: 1.5rem;
      }
    }
  `;
}

function getHomePageContent() {
  return `
    <div class="hero-section">
      <div class="hero-content">
        <h1 class="hero-title">数据结构与算法 A</h1>
        <p class="hero-subtitle">北京大学计算机系核心课程</p>
        <div class="hero-stats">
          <div class="stat-item">
            <div class="stat-number">200+</div>
            <div class="stat-label">课程资料</div>
          </div>
          <div class="stat-item">
            <div class="stat-number">50+</div>
            <div class="stat-label">上机题目</div>
          </div>
          <div class="stat-item">
            <div class="stat-number">1000+</div>
            <div class="stat-label">学生受益</div>
          </div>
        </div>
      </div>
    </div>

    <div class="features-grid">
      <div class="feature-card">
        <div class="feature-icon">🎯</div>
        <h3>课程目标</h3>
        <p>掌握基本数据结构和算法设计方法，培养计算思维和问题解决能力</p>
      </div>
      <div class="feature-card">
        <div class="feature-icon">📚</div>
        <h3>丰富资源</h3>
        <p>包含理论笔记、上机题解、往年试题等全面学习资料</p>
      </div>
      <div class="feature-card">
        <div class="feature-icon">💡</div>
        <h3>学习指导</h3>
        <p>提供学习方法、考试技巧、常见误区等实用指导</p>
      </div>
      <div class="feature-card">
        <div class="feature-icon">🤝</div>
        <h3>助教支持</h3>
        <p>及时答疑、作业批改、学习监督等全方位助教服务</p>
      </div>
    </div>
  `;
}

function getInteractiveScript() {
  return `
    // 移动端菜单切换
    const navToggle = document.querySelector('.nav-toggle');
    const navMenu = document.querySelector('.nav-menu');
    
    if (navToggle && navMenu) {
      navToggle.addEventListener('click', () => {
        navMenu.classList.toggle('active');
      });
    }

    // 平滑滚动
    document.querySelectorAll('a[href^="#"]').forEach(anchor => {
      anchor.addEventListener('click', function (e) {
        e.preventDefault();
        const target = document.querySelector(this.getAttribute('href'));
        if (target) {
          target.scrollIntoView({
            behavior: 'smooth',
            block: 'start'
          });
        }
      });
    });

    // 导航栏滚动效果
    let lastScroll = 0;
    window.addEventListener('scroll', () => {
      const navbar = document.querySelector('.navbar');
      const currentScroll = window.pageYOffset;
      
      if (currentScroll > 100) {
        navbar.style.background = 'rgba(255, 255, 255, 0.98)';
        navbar.style.boxShadow = '0 4px 20px rgba(0, 0, 0, 0.15)';
      } else {
        navbar.style.background = 'rgba(255, 255, 255, 0.95)';
        navbar.style.boxShadow = '0 4px 20px rgba(0, 0, 0, 0.1)';
      }
      
      lastScroll = currentScroll;
    });

    // 代码块复制功能
    document.querySelectorAll('.code-block').forEach(block => {
      const button = document.createElement('button');
      button.className = 'copy-button';
      button.textContent = '复制';
      button.addEventListener('click', () => {
        const code = block.querySelector('code').textContent;
        navigator.clipboard.writeText(code).then(() => {
          button.textContent = '已复制!';
          setTimeout(() => {
            button.textContent = '复制';
          }, 2000);
        });
      });
      block.appendChild(button);
    });

    // 添加CSS样式用于复制按钮
    const style = document.createElement('style');
    style.textContent = \`
      .code-block {
        position: relative;
      }
      .copy-button {
        position: absolute;
        top: 10px;
        right: 10px;
        background: #667eea;
        color: white;
        border: none;
        padding: 0.5rem 1rem;
        border-radius: 6px;
        cursor: pointer;
        font-size: 0.8rem;
        transition: all 0.3s ease;
      }
      .copy-button:hover {
        background: #764ba2;
        transform: translateY(-2px);
      }
    \`;
    document.head.appendChild(style);
  `;
}

// 转换单个文件
function convertFile(inputPath, outputPath) {
  try {
    const content = fs.readFileSync(inputPath, 'utf-8');
    const html = convertMarkdownToHtml(content);
    const title = path.basename(inputPath, '.md');
    const htmlContent = createHTML(title, html);
    fs.writeFileSync(outputPath, htmlContent);
    console.log(`✨ Converted: ${inputPath} -> ${outputPath}`);
  } catch (err) {
    console.error(`❌ Error converting ${inputPath}:`, err.message);
  }
}

// 递归转换目录
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

// 创建课程主页
function createHomePage() {
  const homeContent = `
    <div class="hero-section">
      <div class="hero-content">
        <div class="hero-badge">
          <span class="badge-icon">🎓</span>
          <span>北京大学计算机系</span>
        </div>
        <h1 class="hero-title">数据结构与算法 A</h1>
        <p class="hero-subtitle">2025年秋季学期 · 王乐业老师教学班</p>
        <div class="hero-description">
          <p>掌握基本数据结构和算法设计方法，培养计算思维和问题解决能力</p>
        </div>
        <div class="hero-actions">
          <a href="notes-上机.html" class="btn btn-primary">
            <span>开始学习</span>
            <span class="btn-icon">→</span>
          </a>
          <a href="README.html" class="btn btn-secondary">
            <span>课程介绍</span>
          </a>
        </div>
      </div>
      <div class="hero-visual">
        <div class="floating-card">
          <div class="card-icon">📚</div>
          <div class="card-content">
            <div class="card-title">200+</div>
            <div class="card-desc">课程资料</div>
          </div>
        </div>
        <div class="floating-card">
          <div class="card-icon">💻</div>
          <div class="card-content">
            <div class="card-title">50+</div>
            <div class="card-desc">上机题目</div>
          </div>
        </div>
        <div class="floating-card">
          <div class="card-icon">⭐</div>
          <div class="card-content">
            <div class="card-title">4.8</div>
            <div class="card-desc">课程评分</div>
          </div>
        </div>
      </div>
    </div>

    <div class="quick-access">
      <h2 class="section-title">🚀 快速访问</h2>
      <div class="quick-grid">
        <a href="https://dsa.openjudge.cn/" target="_blank" class="quick-card">
          <div class="quick-icon">🎯</div>
          <div class="quick-content">
            <h3>课程OJ</h3>
            <p>在线编程练习平台</p>
          </div>
        </a>
        <a href="notes-上机.html" class="quick-card">
          <div class="quick-icon">⚙️</div>
          <div class="quick-content">
            <h3>上机笔记</h3>
            <p>实践题解与代码</p>
          </div>
        </a>
        <a href="notes-理论-期中前.html" class="quick-card">
          <div class="quick-icon">📊</div>
          <div class="quick-content">
            <h3>理论笔记</h3>
            <p>知识点详细讲解</p>
          </div>
        </a>
        <a href="往年资料/" class="quick-card">
          <div class="quick-icon">📁</div>
          <div class="quick-content">
            <h3>往年资料</h3>
            <p>历年试题与答案</p>
          </div>
        </a>
      </div>
    </div>

    <div class="course-features">
      <h2 class="section-title">📖 课程特色</h2>
      <div class="features-grid">
        <div class="feature-card">
          <div class="feature-icon">🧠</div>
          <h3>算法思维</h3>
          <p>培养抽象思维和问题解决能力，掌握算法设计的基本方法</p>
        </div>
        <div class="feature-card">
          <div class="feature-icon">⚡</div>
          <h3>高效实现</h3>
          <p>学习各种数据结构的实现原理，理解时间空间复杂度分析</p>
        </div>
        <div class="feature-card">
          <div class="feature-icon">🎯</div>
          <h3>实践导向</h3>
          <p>丰富的上机练习，理论与实际相结合，提升编程能力</p>
        </div>
        <div class="feature-card">
          <div class="feature-icon">📈</div>
          <h3>系统学习</h3>
          <p>从基础到高级，循序渐进，构建完整的知识体系</p>
        </div>
      </div>
    </div>

    <div class="learning-path">
      <h2 class="section-title">🗺️ 学习路径</h2>
      <div class="path-timeline">
        <div class="path-item">
          <div class="path-marker">1</div>
          <div class="path-content">
            <h3>基础数据结构</h3>
            <p>线性表、栈、队列、字符串</p>
            <div class="path-tags">
              <span class="tag">数组</span>
              <span class="tag">链表</span>
              <span class="tag">栈</span>
              <span class="tag">队列</span>
            </div>
          </div>
        </div>
        <div class="path-item">
          <div class="path-marker">2</div>
          <div class="path-content">
            <h3>树形结构</h3>
            <p>二叉树、树、森林、二叉搜索树</p>
            <div class="path-tags">
              <span class="tag">二叉树</span>
              <span class="tag">遍历</span>
              <span class="tag">BST</span>
              <span class="tag">AVL</span>
            </div>
          </div>
        </div>
        <div class="path-item">
          <div class="path-marker">3</div>
          <div class="path-content">
            <h3>图论算法</h3>
            <p>图的存储、遍历、最短路径</p>
            <div class="path-tags">
              <span class="tag">DFS</span>
              <span class="tag">BFS</span>
              <span class="tag">Dijkstra</span>
              <span class="tag">Floyd</span>
            </div>
          </div>
        </div>
        <div class="path-item">
          <div class="path-marker">4</div>
          <div class="path-content">
            <h3>排序与搜索</h3>
            <p>各种排序算法和搜索技术</p>
            <div class="path-tags">
              <span class="tag">快排</span>
              <span class="tag">归并</span>
              <span class="tag">二分</span>
              <span class="tag">哈希</span>
            </div>
          </div>
        </div>
      </div>
    </div>

    <div class="announcements">
      <h2 class="section-title">📢 最新公告</h2>
      <div class="announcement-list">
        <div class="announcement-item urgent">
          <div class="announcement-date">2025-09-10</div>
          <div class="announcement-content">
            <h3>🎯 第三周上机作业已发布</h3>
            <p>请在9月17日前完成栈和队列的相关练习，注意查看作业要求。</p>
          </div>
        </div>
        <div class="announcement-item">
          <div class="announcement-date">2025-09-08</div>
          <div class="announcement-content">
            <h3>📚 第二章理论笔记已更新</h3>
            <p>补充了栈和队列的应用实例，建议在上机前复习。</p>
          </div>
        </div>
        <div class="announcement-item">
          <div class="announcement-date">2025-09-05</div>
          <div class="announcement-content">
            <h3>💬 答疑时间调整</h3>
            <p>本周答疑时间改为周三下午2-4点，地点：理科1号楼1504。</p>
          </div>
        </div>
      </div>
    </div>
  `;
  
  const homeHTML = createHTML('数据结构与算法 A - PKU', homeContent, 'home');
  fs.writeFileSync('docs/index.html', homeHTML);
  console.log('✨ Created: docs/index.html (Homepage with enhanced design)');
}

// 开始转换
console.log('🚀 Starting enhanced website generation...');

// 创建docs目录
if (!fs.existsSync('docs')) {
  fs.mkdirSync('docs', { recursive: true });
}

// 创建课程主页
createHomePage();

// 转换根目录的README.md
if (fs.existsSync('README.md')) {
  convertFile('README.md', 'docs/README.html');
}

// 为每个笔记目录创建索引页面
createEnhancedIndexPage('notes-上机', '上机笔记', '编程实践与题解');
createEnhancedIndexPage('notes-理论-期中前', '理论笔记 - 期中前', '基础理论与算法');
createEnhancedIndexPage('notes-理论-期中后', '理论笔记 - 期中后', '高级算法与应用');

// 转换具体的笔记文件
['notes-上机', 'notes-理论-期中前', 'notes-理论-期中后'].forEach(dir => {
  if (fs.existsSync(dir)) {
    const outputDir = path.join('docs', dir);
    if (!fs.existsSync(outputDir)) {
      fs.mkdirSync(outputDir, { recursive: true });
    }
    convertDirectory(dir, outputDir);
  }
});

// 创建增强的索引页面函数
function createEnhancedIndexPage(dirName, title, description) {
  const content = `
    <div class="page-header">
      <div class="header-content">
        <h1>${title}</h1>
        <p>${description}</p>
      </div>
    </div>

    <div class="content-grid">
      <div class="sidebar">
        <div class="sidebar-card">
          <h3>📋 目录导航</h3>
          <nav class="sidebar-nav">
            <a href="#overview" class="sidebar-link">概述</a>
            <a href="#chapters" class="sidebar-link">章节内容</a>
            <a href="#resources" class="sidebar-link">相关资源</a>
          </nav>
        </div>
        
        <div class="sidebar-card">
          <h3>📊 学习统计</h3>
          <div class="stats-item">
            <span class="stats-label">已完成章节</span>
            <span class="stats-value">12/15</span>
          </div>
          <div class="stats-item">
            <span class="stats-label">练习题目</span>
            <span class="stats-value">85道</span>
          </div>
          <div class="stats-item">
            <span class="stats-label">预计学习时间</span>
            <span class="stats-value">24小时</span>
          </div>
        </div>
      </div>

      <div class="main-content-area">
        <section id="overview" class="content-section">
          <h2>📖 课程概述</h2>
          <p>本部分包含${title}的完整学习资料，涵盖理论知识和实践应用。</p>
          
          <div class="progress-bar">
            <div class="progress-fill" style="width: 80%"></div>
            <span class="progress-text">80% 完成</span>
          </div>
        </section>

        <section id="chapters" class="content-section">
          <h2>📑 章节内容</h2>
          <div class="chapter-grid">
            <div class="chapter-card">
              <div class="chapter-status completed">✓</div>
              <h3>第一章：绪论</h3>
              <p>数据结构基本概念，算法复杂度分析</p>
              <div class="chapter-meta">
                <span class="duration">⏱️ 2小时</span>
                <span class="difficulty">难度：⭐</span>
              </div>
            </div>
            
            <div class="chapter-card">
              <div class="chapter-status completed">✓</div>
              <h3>第二章：线性表</h3>
              <p>顺序表、链表的基本操作和应用</p>
              <div class="chapter-meta">
                <span class="duration">⏱️ 3小时</span>
                <span class="difficulty">难度：⭐⭐</span>
              </div>
            </div>
            
            <div class="chapter-card">
              <div class="chapter-status in-progress">🔄</div>
              <h3>第三章：栈和队列</h3>
              <p>栈和队列的实现及应用，递归算法</p>
              <div class="chapter-meta">
                <span class="duration">⏱️ 4小时</span>
                <span class="difficulty">难度：⭐⭐⭐</span>
              </div>
            </div>
          </div>
        </section>

        <section id="resources" class="content-section">
          <h2>🛠️ 相关资源</h2>
          <div class="resource-list">
            <div class="resource-item">
              <div class="resource-icon">📄</div>
              <div class="resource-content">
                <h4>课件下载</h4>
                <p>课程PPT和教学资料</p>
              </div>
            </div>
            <div class="resource-item">
              <div class="resource-icon">💻</div>
              <div class="resource-content">
                <h4>代码示例</h4>
                <p>完整的代码实现</p>
              </div>
            </div>
            <div class="resource-item">
              <div class="resource-icon">📝</div>
              <div class="resource-content">
                <h4>练习题库</h4>
                <p>配套练习题和答案</p>
              </div>
            </div>
          </div>
        </section>
      </div>
    </div>
  `;
  
  const html = createHTML(`${title} - 数据结构与算法A`, content);
  fs.writeFileSync(`docs/${dirName}.html`, html);
  console.log(`✨ Created: docs/${dirName}.html`);
}

  // 创建助教工作台
  if (fs.existsSync('ta-dashboard.md')) {
    convertFile('ta-dashboard.md', 'docs/ta-dashboard.html');
  }

console.log('🎉 Enhanced website generation completed!');
console.log('📁 Generated files:');
console.log('  - docs/index.html (Homepage with modern design)');
console.log('  - docs/README.html (Enhanced course introduction)');
console.log('  - docs/notes-*.html (Enhanced note pages)');
console.log('  - docs/ta-dashboard.html (TA Dashboard)');
console.log('');
console.log('🚀 To preview locally:');
console.log('  cd docs && python -m http.server 8000');
console.log('  Then visit: http://localhost:8000');
console.log('');
console.log('📱 The website is fully responsive and GitHub Pages compatible!');