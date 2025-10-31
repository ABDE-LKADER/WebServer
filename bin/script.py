#!/usr/bin/env python3
import os
import sys
import html

print("Content-Type: text/html\r\n\r")
print("<html><head><title>CGI Test</title></head><body>")
print("<h1>Hello from python CGI!</h1>")
print("<p>This is a simple Python CGI script.</p>")
print("<h2>Environment Variables:</h2><ul>")
for key, value in sorted(os.environ.items()):
    if key.startswith(('HTTP_', 'REQUEST_', 'SERVER_', 'CONTENT_', 'QUERY_')):
        print(f"<li><strong>{key}:</strong> {value}</li>")
print("</ul>")
print("<h2>Request Method:</h2>")
print(f"<p>{os.environ.get('REQUEST_METHOD', 'Unknown')}</p>")

if os.environ.get('REQUEST_METHOD') == 'POST':
    print("<h2>POST Data:</h2>")
    content_length = os.environ.get('CONTENT_LENGTH', '0')

    print("<p>Reading all stdin:</p>")
    post_data = sys.stdin.read()
    escaped_data = html.escape(post_data)
    print(f"<pre>{escaped_data}</pre>")

print("</body></html>")
