from http.server import BaseHTTPRequestHandler, HTTPServer

class MyHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        self.send_response(200)
        self.send_header("Content-Type", "text/plain")
        self.end_headers()
        self.wfile.write(b"Hello from the server!")

HOST = "localhost"
PORT = 8000

server = HTTPServer((HOST, PORT), MyHandler)

print(f"Server running at http://{HOST}:{PORT}")
server.serve_forever()