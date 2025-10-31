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

# do infinite loop to test timeout
# while true; do :; done

echo "</ul>"
echo "<h2>Request Method:</h2>"
echo "<p>${REQUEST_METHOD:-Unknown}</p>"

if [ "$REQUEST_METHOD" = "POST" ]; then
    while IFS= read -r line || [[ -n "$line" ]]; do
        echo "$line<br>"
    done
fi


echo "</body></html>"

# Test error, Traceback should be logged in .objects/error_log_cgi.log
# error
