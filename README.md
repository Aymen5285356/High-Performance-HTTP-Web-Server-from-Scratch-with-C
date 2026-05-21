
<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<title>C-Pulse — README</title>
<link href="https://fonts.googleapis.com/css2?family=JetBrains+Mono:wght@300;400;500;700;800&family=Syne:wght@400;600;700;800&display=swap" rel="stylesheet">
<style>
  :root {
    --bg: #0a0c0f;
    --surface: #0f1318;
    --surface2: #141920;
    --border: #1e2530;
    --accent: #00d4ff;
    --accent2: #ff4d6d;
    --accent3: #39ff14;
    --text: #e2e8f0;
    --muted: #64748b;
    --dim: #374151;
  }

  * { margin: 0; padding: 0; box-sizing: border-box; }

  body {
    background: var(--bg);
    color: var(--text);
    font-family: 'Syne', sans-serif;
    min-height: 100vh;
    overflow-x: hidden;
  }

  /* Animated grid background */
  body::before {
    content: '';
    position: fixed;
    inset: 0;
    background-image:
      linear-gradient(rgba(0,212,255,0.03) 1px, transparent 1px),
      linear-gradient(90deg, rgba(0,212,255,0.03) 1px, transparent 1px);
    background-size: 40px 40px;
    pointer-events: none;
    z-index: 0;
  }

  /* Glowing orbs */
  body::after {
    content: '';
    position: fixed;
    top: -200px; left: -200px;
    width: 600px; height: 600px;
    background: radial-gradient(circle, rgba(0,212,255,0.06) 0%, transparent 70%);
    pointer-events: none;
    z-index: 0;
    animation: orbFloat 8s ease-in-out infinite;
  }

  @keyframes orbFloat {
    0%, 100% { transform: translate(0, 0); }
    50% { transform: translate(60px, 40px); }
  }

  .container {
    max-width: 900px;
    margin: 0 auto;
    padding: 60px 24px 100px;
    position: relative;
    z-index: 1;
  }

  /* ─── HERO ─── */
  .hero {
    text-align: center;
    padding: 80px 0 60px;
    position: relative;
  }

  .hero-tag {
    display: inline-flex;
    align-items: center;
    gap: 8px;
    background: rgba(0,212,255,0.08);
    border: 1px solid rgba(0,212,255,0.2);
    border-radius: 100px;
    padding: 6px 16px;
    font-family: 'JetBrains Mono', monospace;
    font-size: 11px;
    color: var(--accent);
    letter-spacing: 0.15em;
    text-transform: uppercase;
    margin-bottom: 32px;
    animation: fadeDown 0.6s ease both;
  }

  .hero-tag::before {
    content: '';
    width: 6px; height: 6px;
    background: var(--accent3);
    border-radius: 50%;
    animation: pulse 2s ease infinite;
  }

  @keyframes pulse {
    0%, 100% { box-shadow: 0 0 0 0 rgba(57,255,20,0.4); }
    50% { box-shadow: 0 0 0 6px rgba(57,255,20,0); }
  }

  @keyframes fadeDown {
    from { opacity: 0; transform: translateY(-20px); }
    to { opacity: 1; transform: translateY(0); }
  }

  .hero-title {
    font-family: 'JetBrains Mono', monospace;
    font-size: clamp(52px, 10vw, 96px);
    font-weight: 800;
    letter-spacing: -0.03em;
    line-height: 0.95;
    animation: fadeDown 0.6s 0.1s ease both;
    position: relative;
  }

  .hero-title .c {
    color: var(--accent);
    text-shadow: 0 0 40px rgba(0,212,255,0.5);
  }

  .hero-title .dash {
    color: var(--muted);
  }

  .hero-title .pulse {
    background: linear-gradient(135deg, #ff4d6d, #ff8c42);
    -webkit-background-clip: text;
    -webkit-text-fill-color: transparent;
    background-clip: text;
  }

  .hero-subtitle {
    margin-top: 24px;
    font-size: 16px;
    color: var(--muted);
    line-height: 1.7;
    max-width: 560px;
    margin-left: auto;
    margin-right: auto;
    animation: fadeDown 0.6s 0.2s ease both;
  }

  /* Badges */
  .badges {
    display: flex;
    gap: 8px;
    justify-content: center;
    flex-wrap: wrap;
    margin-top: 32px;
    animation: fadeDown 0.6s 0.3s ease both;
  }

  .badge {
    font-family: 'JetBrains Mono', monospace;
    font-size: 11px;
    padding: 5px 12px;
    border-radius: 4px;
    font-weight: 500;
  }

  .badge-c { background: rgba(0,212,255,0.1); color: var(--accent); border: 1px solid rgba(0,212,255,0.25); }
  .badge-tcp { background: rgba(57,255,20,0.1); color: var(--accent3); border: 1px solid rgba(57,255,20,0.25); }
  .badge-http { background: rgba(255,77,109,0.1); color: var(--accent2); border: 1px solid rgba(255,77,109,0.25); }
  .badge-zero { background: rgba(255,140,66,0.1); color: #ff8c42; border: 1px solid rgba(255,140,66,0.25); }

  /* ─── DIVIDER ─── */
  .divider {
    display: flex;
    align-items: center;
    gap: 16px;
    margin: 48px 0;
    opacity: 0.3;
  }
  .divider::before, .divider::after {
    content: '';
    flex: 1;
    height: 1px;
    background: var(--border);
  }
  .divider span {
    font-family: 'JetBrains Mono', monospace;
    font-size: 10px;
    color: var(--muted);
    letter-spacing: 0.2em;
  }

  /* ─── SECTION ─── */
  .section {
    margin-bottom: 56px;
    animation: fadeUp 0.5s ease both;
  }

  @keyframes fadeUp {
    from { opacity: 0; transform: translateY(24px); }
    to { opacity: 1; transform: translateY(0); }
  }

  .section-header {
    display: flex;
    align-items: center;
    gap: 12px;
    margin-bottom: 24px;
  }

  .section-icon {
    width: 32px; height: 32px;
    border-radius: 8px;
    display: flex;
    align-items: center;
    justify-content: center;
    font-size: 14px;
    flex-shrink: 0;
  }

  .section-icon.cyan { background: rgba(0,212,255,0.1); border: 1px solid rgba(0,212,255,0.2); }
  .section-icon.red { background: rgba(255,77,109,0.1); border: 1px solid rgba(255,77,109,0.2); }
  .section-icon.green { background: rgba(57,255,20,0.1); border: 1px solid rgba(57,255,20,0.2); }
  .section-icon.orange { background: rgba(255,140,66,0.1); border: 1px solid rgba(255,140,66,0.2); }

  .section-title {
    font-size: 13px;
    font-weight: 700;
    text-transform: uppercase;
    letter-spacing: 0.15em;
    color: var(--muted);
  }

  /* ─── OVERVIEW CARD ─── */
  .overview-card {
    background: var(--surface);
    border: 1px solid var(--border);
    border-radius: 16px;
    padding: 32px;
    position: relative;
    overflow: hidden;
  }

  .overview-card::before {
    content: '';
    position: absolute;
    top: 0; left: 0; right: 0;
    height: 1px;
    background: linear-gradient(90deg, transparent, var(--accent), transparent);
    opacity: 0.5;
  }

  .overview-card p {
    font-size: 15px;
    line-height: 1.8;
    color: #94a3b8;
  }

  .overview-card p span {
    color: var(--text);
    font-weight: 600;
  }

  .overview-card p code {
    font-family: 'JetBrains Mono', monospace;
    font-size: 13px;
    color: var(--accent);
    background: rgba(0,212,255,0.08);
    padding: 1px 6px;
    border-radius: 4px;
  }

  /* ─── ARCH DIAGRAM ─── */
  .arch-diagram {
    background: var(--surface);
    border: 1px solid var(--border);
    border-radius: 16px;
    padding: 32px;
    font-family: 'JetBrains Mono', monospace;
    font-size: 13px;
    position: relative;
    overflow: hidden;
  }

  .arch-flow {
    display: flex;
    flex-direction: column;
    gap: 0;
    position: relative;
    z-index: 1;
  }

  .arch-row {
    display: flex;
    align-items: center;
    gap: 12px;
  }

  .arch-node {
    border-radius: 10px;
    padding: 12px 20px;
    font-size: 13px;
    font-weight: 500;
    white-space: nowrap;
    position: relative;
  }

  .node-browser {
    background: rgba(0,212,255,0.08);
    border: 1px solid rgba(0,212,255,0.3);
    color: var(--accent);
  }

  .node-tcp {
    background: rgba(57,255,20,0.08);
    border: 1px solid rgba(57,255,20,0.3);
    color: var(--accent3);
  }

  .node-http {
    background: rgba(255,140,66,0.08);
    border: 1px solid rgba(255,140,66,0.3);
    color: #ff8c42;
  }

  .node-cpulse {
    background: rgba(255,77,109,0.08);
    border: 1px solid rgba(255,77,109,0.3);
    color: var(--accent2);
  }

  .node-fs {
    background: rgba(139,92,246,0.08);
    border: 1px solid rgba(139,92,246,0.3);
    color: #a78bfa;
  }

  .arch-arrow {
    color: var(--dim);
    font-size: 16px;
    display: flex;
    align-items: center;
    gap: 4px;
    flex: 1;
  }

  .arch-arrow-line {
    flex: 1;
    height: 1px;
    background: linear-gradient(90deg, var(--dim), transparent);
  }

  .arch-label {
    font-size: 10px;
    color: var(--muted);
    letter-spacing: 0.1em;
    text-transform: uppercase;
    margin-left: 8px;
  }

  /* ─── FEATURES GRID ─── */
  .features-grid {
    display: grid;
    grid-template-columns: repeat(2, 1fr);
    gap: 12px;
  }

  @media (max-width: 600px) {
    .features-grid { grid-template-columns: 1fr; }
  }

  .feature-card {
    background: var(--surface);
    border: 1px solid var(--border);
    border-radius: 12px;
    padding: 20px;
    transition: border-color 0.2s, background 0.2s;
    position: relative;
    overflow: hidden;
  }

  .feature-card:hover {
    border-color: rgba(0,212,255,0.2);
    background: var(--surface2);
  }

  .feature-card::after {
    content: '';
    position: absolute;
    inset: 0;
    background: radial-gradient(circle at top left, rgba(0,212,255,0.03), transparent 60%);
    pointer-events: none;
  }

  .feature-icon {
    font-size: 20px;
    margin-bottom: 10px;
  }

  .feature-title {
    font-size: 13px;
    font-weight: 700;
    color: var(--text);
    margin-bottom: 6px;
  }

  .feature-desc {
    font-size: 12px;
    color: var(--muted);
    line-height: 1.6;
  }

  /* ─── CODE BLOCK ─── */
  .code-block {
    background: #070a0e;
    border: 1px solid var(--border);
    border-radius: 12px;
    overflow: hidden;
    margin-top: 12px;
  }

  .code-header {
    display: flex;
    align-items: center;
    justify-content: space-between;
    padding: 10px 16px;
    background: var(--surface);
    border-bottom: 1px solid var(--border);
  }

  .code-dots {
    display: flex;
    gap: 6px;
  }

  .code-dot {
    width: 10px; height: 10px;
    border-radius: 50%;
  }
  .dot-red { background: #ff5f57; }
  .dot-yellow { background: #ffbd2e; }
  .dot-green { background: #28c840; }

  .code-lang {
    font-family: 'JetBrains Mono', monospace;
    font-size: 10px;
    color: var(--muted);
    text-transform: uppercase;
    letter-spacing: 0.15em;
  }

  .code-body {
    padding: 20px;
    font-family: 'JetBrains Mono', monospace;
    font-size: 13px;
    line-height: 1.7;
    overflow-x: auto;
  }

  .code-comment { color: #4a5568; }
  .code-keyword { color: #ff79c6; }
  .code-fn { color: #50fa7b; }
  .code-str { color: #f1fa8c; }
  .code-num { color: #bd93f9; }
  .code-type { color: var(--accent); }
  .code-var { color: #ffb86c; }
  .code-op { color: #ff5555; }
  .code-plain { color: #f8f8f2; }

  /* ─── STEPS ─── */
  .steps {
    display: flex;
    flex-direction: column;
    gap: 0;
    position: relative;
  }

  .steps::before {
    content: '';
    position: absolute;
    left: 18px;
    top: 0; bottom: 0;
    width: 1px;
    background: linear-gradient(to bottom, var(--accent), transparent);
    opacity: 0.2;
  }

  .step {
    display: flex;
    gap: 20px;
    padding: 16px 0;
    position: relative;
  }

  .step-num {
    width: 36px; height: 36px;
    border-radius: 50%;
    border: 1px solid var(--border);
    background: var(--surface);
    display: flex;
    align-items: center;
    justify-content: center;
    font-family: 'JetBrains Mono', monospace;
    font-size: 12px;
    font-weight: 700;
    color: var(--accent);
    flex-shrink: 0;
    position: relative;
    z-index: 1;
  }

  .step-content {
    padding-top: 6px;
    flex: 1;
  }

  .step-title {
    font-size: 14px;
    font-weight: 700;
    color: var(--text);
    margin-bottom: 4px;
  }

  .step-desc {
    font-size: 13px;
    color: var(--muted);
    line-height: 1.6;
  }

  .step-desc code {
    font-family: 'JetBrains Mono', monospace;
    font-size: 12px;
    color: var(--accent);
    background: rgba(0,212,255,0.08);
    padding: 1px 6px;
    border-radius: 4px;
  }

  /* ─── SKILLS ─── */
  .skills-list {
    display: flex;
    flex-direction: column;
    gap: 8px;
  }

  .skill-item {
    display: flex;
    align-items: flex-start;
    gap: 12px;
    background: var(--surface);
    border: 1px solid var(--border);
    border-radius: 10px;
    padding: 14px 18px;
    font-size: 13px;
    line-height: 1.5;
  }

  .skill-dot {
    width: 6px; height: 6px;
    border-radius: 50%;
    background: var(--accent);
    flex-shrink: 0;
    margin-top: 4px;
    box-shadow: 0 0 8px rgba(0,212,255,0.5);
  }

  .skill-dot.red { background: var(--accent2); box-shadow: 0 0 8px rgba(255,77,109,0.5); }
  .skill-dot.green { background: var(--accent3); box-shadow: 0 0 8px rgba(57,255,20,0.5); }
  .skill-dot.orange { background: #ff8c42; box-shadow: 0 0 8px rgba(255,140,66,0.5); }
  .skill-dot.purple { background: #a78bfa; box-shadow: 0 0 8px rgba(167,139,250,0.5); }

  .skill-text { color: #94a3b8; }
  .skill-text strong { color: var(--text); }

  /* ─── FOOTER ─── */
  .footer {
    margin-top: 80px;
    padding-top: 32px;
    border-top: 1px solid var(--border);
    text-align: center;
  }

  .footer-sig {
    font-family: 'JetBrains Mono', monospace;
    font-size: 12px;
    color: var(--dim);
  }

  .footer-sig span { color: var(--muted); }

  /* ─── TERMINAL DEMO ─── */
  .terminal {
    background: #050709;
    border: 1px solid var(--border);
    border-radius: 12px;
    overflow: hidden;
  }

  .terminal-bar {
    background: var(--surface);
    border-bottom: 1px solid var(--border);
    padding: 10px 16px;
    display: flex;
    align-items: center;
    gap: 12px;
  }

  .terminal-title {
    font-family: 'JetBrains Mono', monospace;
    font-size: 11px;
    color: var(--muted);
    flex: 1;
    text-align: center;
  }

  .terminal-body {
    padding: 20px;
    font-family: 'JetBrains Mono', monospace;
    font-size: 13px;
    line-height: 1.8;
  }

  .t-prompt { color: var(--accent3); }
  .t-cmd { color: var(--text); }
  .t-output { color: #64748b; }
  .t-success { color: var(--accent3); }
  .t-port { color: var(--accent); }
  .t-req { color: #ff8c42; }
  .t-status { color: var(--accent2); }

  /* ─── INLINE HIGHLIGHT BOX ─── */
  .highlight-box {
    background: rgba(0,212,255,0.04);
    border: 1px solid rgba(0,212,255,0.12);
    border-left: 3px solid var(--accent);
    border-radius: 0 10px 10px 0;
    padding: 16px 20px;
    font-size: 13px;
    color: #94a3b8;
    line-height: 1.7;
    margin-top: 16px;
  }

  .highlight-box strong { color: var(--accent); }

  /* Staggered animation */
  .section:nth-child(1) { animation-delay: 0.1s; }
  .section:nth-child(2) { animation-delay: 0.15s; }
  .section:nth-child(3) { animation-delay: 0.2s; }
  .section:nth-child(4) { animation-delay: 0.25s; }
  .section:nth-child(5) { animation-delay: 0.3s; }
  .section:nth-child(6) { animation-delay: 0.35s; }
</style>
</head>
<body>
<div class="container">

  <!-- ─── HERO ─── -->
  <div class="hero">
    <div class="hero-tag">Systems Programming · C Language · Networking</div>
    <h1 class="hero-title">
      <span class="c">C</span><span class="dash">-</span><span class="pulse">Pulse</span>
    </h1>
    <p class="hero-subtitle">
      خادم ويب حقيقي ومصغر مبني من الصفر بلغة C — بدون أي مكتبات خارجية.
      يحوّل جهازك إلى سيرفر حقيقي يتحدث HTTP فوق TCP/IP.
    </p>
    <div class="badges">
      <span class="badge badge-c">C Language</span>
      <span class="badge badge-tcp">TCP/IP</span>
      <span class="badge badge-http">HTTP/1.1</span>
      <span class="badge badge-zero">Zero Dependencies</span>
    </div>
  </div>

  <!-- ─── OVERVIEW ─── -->
  <div class="section">
    <div class="section-header">
      <div class="section-icon cyan">📡</div>
      <span class="section-title">Overview</span>
    </div>
    <div class="overview-card">
      <p>
        <span>C-Pulse</span> هو خادم ويب (<code>Web Server</code>) مكتوب بالكامل بلغة <span>C</span> دون الاعتماد
        على أي مكتبات خارجية — فقط الـ <code>Sockets API</code> الخاص بنظام التشغيل وبروتوكولات الشبكة الأساسية.
        يستمع المشروع لطلبات المتصفحات الواردة عبر بروتوكول <code>TCP/IP</code>، يُحلّل رسائل <code>HTTP</code>،
        يقرأ ملفات <code>HTML</code> من الهارد ديسك، ثم يُرسلها كاستجابة حقيقية لتظهر في المتصفح كصفحة ويب.
      </p>
    </div>
  </div>

  <!-- ─── ARCHITECTURE ─── -->
  <div class="section">
    <div class="section-header">
      <div class="section-icon orange">🔗</div>
      <span class="section-title">How It Works</span>
    </div>
    <div class="arch-diagram">
      <div class="arch-flow">

        <div class="arch-row">
          <div class="arch-node node-browser">🌐 Browser (Chrome)</div>
          <div class="arch-arrow">
            <span style="color:var(--dim)">──</span>
            <span style="color:#ff8c42; font-size:11px"> HTTP Request </span>
            <span style="color:var(--dim)">──▶</span>
          </div>
          <div class="arch-node node-tcp">TCP Socket</div>
        </div>

        <div style="padding: 6px 0 6px 72px; color: var(--dim); font-size:18px;">↓</div>

        <div class="arch-row">
          <div class="arch-node node-cpulse">⚡ C-Pulse Server</div>
          <div class="arch-arrow">
            <span style="color:var(--dim)">──</span>
            <span style="color:#a78bfa; font-size:11px"> read() </span>
            <span style="color:var(--dim)">──▶</span>
          </div>
          <div class="arch-node node-fs">📂 File System</div>
        </div>

        <div style="padding: 6px 0 6px 72px; color: var(--dim); font-size:18px;">↓</div>

        <div class="arch-row">
          <div class="arch-node node-http">📨 HTTP Response</div>
          <div class="arch-arrow">
            <span style="color:var(--dim)">──</span>
            <span style="color:var(--accent3); font-size:11px"> send() </span>
            <span style="color:var(--dim)">──▶</span>
          </div>
          <div class="arch-node node-browser">🌐 Rendered Page</div>
        </div>

      </div>
    </div>

    <div class="highlight-box">
      <strong>البروتوكول بالكامل يدوي:</strong> لا <code>libcurl</code>، لا <code>libevent</code>، لا frameworks.
      كل <code>header</code> وكل <code>status code</code> يُكتب يدوياً بـ C خالصة.
    </div>
  </div>

  <!-- ─── FEATURES ─── -->
  <div class="section">
    <div class="section-header">
      <div class="section-icon green">✦</div>
      <span class="section-title">Features</span>
    </div>
    <div class="features-grid">
      <div class="feature-card">
        <div class="feature-icon">🔌</div>
        <div class="feature-title">TCP Socket Listener</div>
        <div class="feature-desc">يفتح socket حقيقي على منفذ محدد ويستمع لأي اتصال وارد من المتصفح أو أي عميل HTTP.</div>
      </div>
      <div class="feature-card">
        <div class="feature-icon">🔍</div>
        <div class="feature-title">HTTP Request Parser</div>
        <div class="feature-desc">يُحلّل رسالة HTTP الواردة ويستخرج الـ method والـ path وأي headers ضرورية يدوياً.</div>
      </div>
      <div class="feature-card">
        <div class="feature-icon">📁</div>
        <div class="feature-title">Static File Serving</div>
        <div class="feature-desc">يقرأ ملفات HTML (وما يرافقها) من الملف الجذر ويُرسلها كـ response كاملة للمتصفح.</div>
      </div>
      <div class="feature-card">
        <div class="feature-icon">📤</div>
        <div class="feature-title">HTTP Response Builder</div>
        <div class="feature-desc">يبني رسالة HTTP/1.1 كاملة مع status line وheaders صحيحة مثل <code>Content-Length</code>.</div>
      </div>
      <div class="feature-card">
        <div class="feature-icon">⚠️</div>
        <div class="feature-title">Error Handling (404)</div>
        <div class="feature-desc">يُرسل صفحة خطأ واضحة عند عدم وجود الملف المطلوب بدلاً من انهيار البرنامج.</div>
      </div>
      <div class="feature-card">
        <div class="feature-icon">🔁</div>
        <div class="feature-title">Persistent Connection Loop</div>
        <div class="feature-desc">يظل السيرفر يعمل في حلقة لا نهائية لاستقبال طلبات متعددة بدون إعادة تشغيل.</div>
      </div>
    </div>
  </div>

  <!-- ─── CODE SNIPPET ─── -->
  <div class="section">
    <div class="section-header">
      <div class="section-icon cyan">⌨️</div>
      <span class="section-title">Core Code — Socket Setup</span>
    </div>
    <div class="code-block">
      <div class="code-header">
        <div class="code-dots">
          <div class="code-dot dot-red"></div>
          <div class="code-dot dot-yellow"></div>
          <div class="code-dot dot-green"></div>
        </div>
        <span class="code-lang">server.c</span>
      </div>
      <div class="code-body"><span class="code-comment">// Create TCP socket</span>
<span class="code-type">int</span> <span class="code-var">server_fd</span> = <span class="code-fn">socket</span>(<span class="code-var">AF_INET</span>, <span class="code-var">SOCK_STREAM</span>, <span class="code-num">0</span>);

<span class="code-comment">// Bind to port 8080</span>
<span class="code-keyword">struct</span> <span class="code-type">sockaddr_in</span> <span class="code-var">address</span>;
<span class="code-var">address</span>.<span class="code-var">sin_family</span>      = <span class="code-var">AF_INET</span>;
<span class="code-var">address</span>.<span class="code-var">sin_addr.s_addr</span> = <span class="code-var">INADDR_ANY</span>;
<span class="code-var">address</span>.<span class="code-var">sin_port</span>        = <span class="code-fn">htons</span>(<span class="code-num">8080</span>);

<span class="code-fn">bind</span>(<span class="code-var">server_fd</span>, (<span class="code-keyword">struct</span> <span class="code-type">sockaddr</span> *)&<span class="code-var">address</span>, <span class="code-keyword">sizeof</span>(<span class="code-var">address</span>));
<span class="code-fn">listen</span>(<span class="code-var">server_fd</span>, <span class="code-num">10</span>);

<span class="code-comment">// Accept & respond in a loop</span>
<span class="code-keyword">while</span> (<span class="code-num">1</span>) {
    <span class="code-type">int</span> <span class="code-var">client_fd</span> = <span class="code-fn">accept</span>(<span class="code-var">server_fd</span>, <span class="code-var">NULL</span>, <span class="code-var">NULL</span>);
    <span class="code-fn">handle_request</span>(<span class="code-var">client_fd</span>);
    <span class="code-fn">close</span>(<span class="code-var">client_fd</span>);
}</div>
    </div>
  </div>

  <!-- ─── TERMINAL OUTPUT ─── -->
  <div class="section">
    <div class="section-header">
      <div class="section-icon green">▶</div>
      <span class="section-title">Running C-Pulse</span>
    </div>
    <div class="terminal">
      <div class="terminal-bar">
        <div class="code-dots">
          <div class="code-dot dot-red"></div>
          <div class="code-dot dot-yellow"></div>
          <div class="code-dot dot-green"></div>
        </div>
        <span class="terminal-title">bash — ~/c-pulse</span>
      </div>
      <div class="terminal-body">
<span class="t-prompt">$ </span><span class="t-cmd">gcc server.c -o c-pulse</span>
<span class="t-output">Compilation successful — 0 errors, 0 warnings</span>

<span class="t-prompt">$ </span><span class="t-cmd">./c-pulse</span>
<span class="t-success">✔ C-Pulse listening on </span><span class="t-port">http://localhost:8080</span>

<span class="t-req">[GET]</span> <span class="t-output">/index.html</span>  →  <span class="t-status">200 OK</span>  <span class="t-output">(1.2ms)</span>
<span class="t-req">[GET]</span> <span class="t-output">/about.html</span>  →  <span class="t-status">200 OK</span>  <span class="t-output">(0.9ms)</span>
<span class="t-req">[GET]</span> <span class="t-output">/missing.html</span> →  <span class="t-status" style="color:#ff4d6d">404 Not Found</span>  <span class="t-output">(0.4ms)</span>
      </div>
    </div>
  </div>

  <!-- ─── HOW TO RUN ─── -->
  <div class="section">
    <div class="section-header">
      <div class="section-icon orange">🚀</div>
      <span class="section-title">Getting Started</span>
    </div>
    <div class="steps">
      <div class="step">
        <div class="step-num">01</div>
        <div class="step-content">
          <div class="step-title">Clone the Repository</div>
          <div class="step-desc">
            <code>git clone https://github.com/username/c-pulse.git</code><br>
            <code>cd c-pulse</code>
          </div>
        </div>
      </div>
      <div class="step">
        <div class="step-num">02</div>
        <div class="step-content">
          <div class="step-title">Compile with GCC</div>
          <div class="step-desc">
            لا توجد تبعيات — فقط <code>gcc server.c -o c-pulse</code><br>
            يعمل على أي نظام Linux أو macOS.
          </div>
        </div>
      </div>
      <div class="step">
        <div class="step-num">03</div>
        <div class="step-content">
          <div class="step-title">Run the Server</div>
          <div class="step-desc">
            <code>./c-pulse</code> — السيرفر سيبدأ الاستماع على المنفذ <code>8080</code>.
          </div>
        </div>
      </div>
      <div class="step">
        <div class="step-num">04</div>
        <div class="step-content">
          <div class="step-title">Open in Browser</div>
          <div class="step-desc">
            افتح <code>http://localhost:8080/index.html</code> في Chrome أو Firefox وشاهد صفحتك تُعرض من سيرفرك.
          </div>
        </div>
      </div>
    </div>
  </div>

  <!-- ─── SKILLS DEMONSTRATED ─── -->
  <div class="section">
    <div class="section-header">
      <div class="section-icon red">🧠</div>
      <span class="section-title">Skills Demonstrated</span>
    </div>
    <div class="skills-list">
      <div class="skill-item">
        <div class="skill-dot"></div>
        <span class="skill-text"><strong>Systems Programming بلغة C</strong> — إدارة الذاكرة يدوياً، التعامل مع الـ file descriptors، وكتابة كود منخفض المستوى بدون أي تجريد.</span>
      </div>
      <div class="skill-item">
        <div class="skill-dot green"></div>
        <span class="skill-text"><strong>Sockets API (POSIX)</strong> — إنشاء TCP sockets، الربط بالمنافذ، الاستماع للاتصالات، وقبول العملاء باستخدام <code>socket()</code> / <code>bind()</code> / <code>listen()</code> / <code>accept()</code>.</span>
      </div>
      <div class="skill-item">
        <div class="skill-dot orange"></div>
        <span class="skill-text"><strong>HTTP Protocol Internals</strong> — فهم كواليس بروتوكول HTTP: تحليل الطلبات، بناء الاستجابات، وتطبيق الـ status codes يدوياً.</span>
      </div>
      <div class="skill-item">
        <div class="skill-dot red"></div>
        <span class="skill-text"><strong>TCP/IP Networking</strong> — فهم عميق لمكدس الشبكات: كيف تنتقل البيانات من المتصفح إلى السيرفر عبر طبقات الشبكة.</span>
      </div>
      <div class="skill-item">
        <div class="skill-dot purple"></div>
        <span class="skill-text"><strong>File I/O in C</strong> — قراءة الملفات من الهارد ديسك بـ <code>fopen</code> / <code>fread</code> / <code>fclose</code> وإرسال محتواها مباشرة عبر الـ socket.</span>
      </div>
    </div>
  </div>

  <!-- ─── FOOTER ─── -->
  <div class="footer">
    <p class="footer-sig">
      Built with <span>♥</span> and raw C — <span>C-Pulse</span> · Zero Dependencies · Real Sockets · Real HTTP
    </p>
  </div>

</div>
</body>
</html>
