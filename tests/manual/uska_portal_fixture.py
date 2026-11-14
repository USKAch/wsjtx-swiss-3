"""Loopback-only portal fixture for manual screenshots; never contacts USKA.

Run with Python, then set USKA/PortalUrl in a separate demo profile to
http://127.0.0.1:8765/submit. Create an empty file named warning, reject,
no-contests or uncertain in the output directory to select that response.
POST bodies are saved locally so generated Cabrillo content can be checked.
"""

import argparse
from http.server import BaseHTTPRequestHandler, HTTPServer
from pathlib import Path
from urllib.parse import parse_qs, urlsplit


class Portal(BaseHTTPRequestHandler):
    def send_html(self, html, status=200, location=None):
        body = html.encode("utf-8")
        self.send_response(status)
        self.send_header("Content-Type", "text/html; charset=utf-8")
        self.send_header("Content-Length", str(len(body)))
        if location:
            self.send_header("Location", location)
        self.end_headers()
        self.wfile.write(body)

    def do_GET(self):
        options = "" if (self.server.output / "no-contests").exists() else (
            '<option value="xmas1">Christmas Contest Digital 1 2026</option>'
            '<option value="xmas2">Christmas Contest Digital 2 2026</option>'
        )
        self.send_html('<h1 class="title">Step 1: Select contest</h1>'
                       '<select id="contest">' + options + '</select>')

    def do_POST(self):
        step = parse_qs(urlsplit(self.path).query).get("step", [""])[0]
        body = self.rfile.read(int(self.headers.get("Content-Length", 0)))
        if step not in {"2", "3", "4"}:
            self.send_html("Unknown step", 400)
            return
        (self.server.output / f"step-{step}.bin").write_bytes(body)
        if step == "2":
            if (self.server.output / "reject").exists():
                self.send_html('<h1 class="title">Step 1: Select contest</h1>'
                               '<article class="message is-danger"><li>Demonstration: invalid QSO.</li></article>')
                return
            warning = ('<article class="message is-warning"><li>Demonstration: check this QSO.</li></article>'
                       if (self.server.output / "warning").exists() else "")
            self.send_html('<h1 class="title">Step 2: Check log</h1>' + warning
                           + '<select id="category"><option value="SOAB-Digital-HP" selected>'
                           'SOAB-Digital-HP</option></select>')
        elif step == "3":
            self.send_html('<h1 class="title">Step 3: Declaration</h1>')
        elif (self.server.output / "uncertain").exists():
            self.send_html("Demonstration: unexpected confirmation", 200)
        else:
            self.send_html("", 303, "/soapbox?submitted=1")


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--output", type=Path, required=True)
    args = parser.parse_args()
    args.output.mkdir(parents=True, exist_ok=True)
    server = HTTPServer(("127.0.0.1", 8765), Portal)
    server.output = args.output
    print("Demo portal: http://127.0.0.1:8765/submit", flush=True)
    server.serve_forever()
