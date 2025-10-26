#!/usr/bin/env bash

echo "Content-Type: text/html"
echo ""
echo "<html><head><title>CGI Test</title></head><body>"
echo "<h1>Hello from Bash CGI!</h1>"
echo "<p>This is a simple Bash CGI script.</p>"
echo "<h2>Environment Variables:</h2><ul>"

# Sort and display relevant environment variables
for var in $(compgen -e | sort); do
    if [[ $var == HTTP_* ]] || [[ $var == REQUEST_* ]] || [[ $var == SERVER_* ]] || [[ $var == CONTENT_* ]] || [[ $var == QUERY_* ]]; then
        echo "<li><strong>$var:</strong> ${!var}</li>"
    fi
done

echo "</ul>"
echo "<h2>Request Method:</h2>"
echo "<p>${REQUEST_METHOD:-Unknown}</p>"

if [ "$REQUEST_METHOD" = "POST" ]; then
    echo "<h2>POST Data:</h2>"
    CONTENT_LENGTH=${CONTENT_LENGTH:-0}
    if [ "$CONTENT_LENGTH" -gt 0 ]; then
        POST_DATA=$(head -c "$CONTENT_LENGTH")
        echo "<pre>$POST_DATA</pre>"
    fi
fi

echo "</body></html>"
