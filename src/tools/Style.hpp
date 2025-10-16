#ifndef STYLE_HPP
# define STYLE_HPP

# define STYLE \
    "<style>" \
    "@import url('https://fonts.googleapis.com/css2?family=Fira+Code:wght@300;400;500;700&display=swap');" \
    "*{margin:0;padding:0;box-sizing:border-box}" \
    "body{background:linear-gradient(135deg,#0a0a0a,#1a1a1a 25%,#0d1117 75%,#000);color:#00ff41;" \
        "font-family:'Fira Code',monospace;min-height:100vh;display:flex;align-items:center;justify-content:center}" \
    ".c{max-width:1000px;margin:0 auto;padding:24px}" \
    "h1{margin:0 0 8px;font-weight:700;text-shadow:0 0 12px #00ff41}" \
    "hr{border:0;height:1px;background:linear-gradient(90deg,transparent,rgba(0,255,65,.3) 10%,rgba(0,255,65,.3)" \
        "90%,transparent);margin:10px 0 16px}" \
    ".e{text-align:center}" \
    ".e h1{font-size:8rem;line-height:1;margin:0}" \
    ".e hr{border:0;height:1px;background:linear-gradient(90deg,transparent,rgba(0,255,65,.5) 20%,rgba(0,255,65,.5)" \
        "80%,transparent);width:80%;margin:24px auto 20px;max-width:400px}" \
    ".e p{font-size:1.5rem;margin-top:10px;font-weight:500;opacity:.9}" \
    ".f{position:fixed;bottom:20px;left:50%;transform:translateX(-50%);font-size:.9rem;opacity:.5}" \
    ".l{display:grid;gap:12px}" \
    ".i a{display:inline-block;color:#00ff41;text-decoration:none;border:1px solid #00ff41;" \
        "padding:6px 12px;border-radius:6px;background:linear-gradient(45deg,rgba(0,255,65,.08)," \
        "rgba(0,255,65,.18));font-weight:500;letter-spacing:1px;transition:all .3s ease}" \
    ".i a:hover{background:#00ff41;color:#000;box-shadow:0 0 14px rgba(0,255,65,.5)}" \
    "</style>"

#endif
