# 🚀 数据结构与算法A课程网站部署指南

## ✨ 新功能介绍

这次更新为你创建了一个**现代化、美观、功能丰富**的课程网站，专为助教工作优化：

### 🎨 视觉设计
- **渐变背景**：现代化的渐变色彩搭配
- **毛玻璃效果**：半透明卡片设计
- **交互动画**：悬停效果、平滑过渡
- **响应式布局**：完美适配移动端

### 📚 功能模块
- **课程主页**：美观的展示页面，包含课程特色、学习路径
- **导航栏**：下拉菜单，分类清晰
- **助教工作台**：专为TA设计的管理面板
- **笔记系统**：理论笔记和上机笔记分类展示
- **资源管理**：课件、代码、题库的集中管理

### 🔧 助教专用功能
- **课程统计**：学生数量、作业提交率、课程评分
- **待办事项**：任务管理清单
- **进度跟踪**：各章节学习情况可视化
- **答疑管理**：学生问题记录和状态跟踪
- **资源管理**：教学资料、作业模板、成绩表格

## 🚀 部署步骤

### 方法1：GitHub Pages（推荐）

1. **启用GitHub Pages**
   ```bash
   # 推送代码到GitHub
   git add .
   git commit -m "Add enhanced course website with modern design"
   git push origin github-pages-config
   ```

2. **在GitHub上配置**
   - 进入仓库的 Settings → Pages
   - 选择 Source 为 "Deploy from a branch"
   - 选择 Branch 为 "github-pages-config" 和 "/ (root)"
   - 点击 Save

3. **访问网站**
   - 等待几分钟让GitHub构建
   - 访问 `https://ICUlizhi.github.io/Data-Structure-and-Algorithm-A-of-pku`

### 方法2：Jekyll原生支持

1. **使用Jekyll主题**
   - 我已经创建了 `_config.yml` 配置文件
   - 系统会自动用Jekyll渲染Markdown文件
   - 适合简单的内容展示

2. **访问地址**
   - `https://ICUlizhi.github.io/Data-Structure-and-Algorithm-A-of-pku`

### 方法3：GitHub Actions自动化

1. **启用GitHub Actions**
   - 进入 Settings → Pages
   - 选择 Source 为 "GitHub Actions"
   - 推送代码后会自动构建和部署

2. **自动构建流程**
   - 每次推送都会触发自动构建
   - Node.js会转换Markdown为美观的HTML
   - 生成的文件自动部署到GitHub Pages

## 📱 本地预览

### 快速预览（推荐）
```bash
# 进入docs目录
cd docs

# 启动本地服务器
python -m http.server 8000

# 访问 http://localhost:8000
```

### 完整构建流程
```bash
# 安装依赖（可选）
npm install

# 构建网站
npm run build

# 本地预览
npm run serve
```

## 🎯 网站结构

```
docs/
├── index.html              # 课程主页（美观设计）
├── README.html             # 课程介绍
├── ta-dashboard.html       # 助教工作台
├── notes-上机/             # 上机笔记
├── notes-理论-期中前/      # 理论笔记（期中前）
├── notes-理论-期中后/      # 理论笔记（期中后）
└── 往年资料/              # 历年资料
```

## 🔗 重要链接

### 课程资源
- **课程OJ**: http://dsa.openjudge.cn/
- **MOOC课程**: https://www.icourse163.org/course/PKU-1002534001
- **MOOC OJ**: http://dsalgo.openjudge.cn/
- **PKUHUB**: https://pkuhub.cn/course/1830

### 网站页面
- **主页**: `/index.html`
- **助教工作台**: `/ta-dashboard.html`
- **上机笔记**: `/notes-上机.html`
- **理论笔记**: `/notes-理论-期中前.html`
- **课程介绍**: `/README.html`

## 🎨 自定义样式

### 颜色主题
在 `build.js` 的 `getEnhancedStyles()` 函数中可以修改：
- `--primary-color`: 主色调
- `--secondary-color`: 辅助色
- `--accent-color`: 强调色
- `--success/warning/error/info-color`: 状态颜色

### 布局调整
- 修改CSS变量调整圆角、阴影、间距
- 调整媒体查询适配不同屏幕尺寸
- 添加新的动画效果

## 📊 功能使用建议

### 作为助教的使用流程：

1. **每日查看助教工作台**
   - 检查待办事项
   - 查看作业提交情况
   - 处理答疑问题

2. **作业管理**
   - 发布新作业
   - 批改作业
   - 录入成绩

3. **学生支持**
   - 回答学生问题
   - 更新学习资料
   - 发布课程公告

4. **数据分析**
   - 跟踪学习进度
   - 分析作业表现
   - 识别困难学生

## 🛠️ 技术特色

### 现代化设计
- **CSS Grid & Flexbox**: 现代布局技术
- **CSS Variables**: 主题色彩系统
- **Backdrop Filter**: 毛玻璃效果
- **CSS Animations**: 流畅动画

### GitHub Pages优化
- **纯静态**: 无需服务器端处理
- **轻量级**: 快速加载
- **兼容性**: 支持所有现代浏览器
- **可访问性**: 符合Web标准

### 响应式设计
- **移动优先**: 从小屏幕开始设计
- **断点系统**: 768px, 480px自适应
- **触摸友好**: 适合移动设备操作
- **性能优化**: 图片和代码优化

## 🔧 故障排除

### 常见问题

1. **页面显示异常**
   - 检查网络连接
   - 清除浏览器缓存
   - 尝试不同浏览器

2. **GitHub Pages部署失败**
   - 确认仓库为public
   - 检查分支设置
   - 查看Actions日志

3. **样式加载问题**
   - 确认CSS文件路径正确
   - 检查浏览器控制台错误
   - 验证HTML结构完整性

### 获取帮助
- 提交GitHub Issue
- 查看浏览器开发者工具
- 参考GitHub Pages文档

## 📈 更新计划

### 即将推出
- [ ] 学生个人学习进度页面
- [ ] 作业提交系统
- [ ] 在线编程环境集成
- [ ] 讨论区功能
- [ ] 数据统计图表

### 长期规划
- [ ] AI辅助答疑系统
- [ ] 个性化学习推荐
- [ ] 移动端App
- [ ] 虚拟现实教学内容

---

**🎉 恭喜！** 你现在拥有了一个专业、美观、功能完善的课程网站，能够大大提升教学效率和学生的学习体验！

如有问题或建议，欢迎提交Issue或Pull Request。祝教学顺利！ 🎓✨

*最后更新：2025年9月10日*