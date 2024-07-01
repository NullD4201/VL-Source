from http.server import BaseHTTPRequestHandler, HTTPServer
import os

# HTTP 요청을 처리하는 핸들러 클래스 정의
class ImageHandler(BaseHTTPRequestHandler):
    
    # POST 요청 처리 함수
    def do_POST(self):
        content_length = int(self.headers['Content-Length'])
        name = self.headers['Image-Name']
        post_data = self.rfile.read(content_length)
        
        # 클라이언트로부터 받은 이미지 데이터를 파일로 저장
        with open(name+'.png', 'wb') as f:
            f.write(post_data)
        
        self.send_response(200)
        self.end_headers()
        self.wfile.write(b'Image received and saved successfully.')
        
    def do_GET(self):
        image_name = self.path.strip('/')
        image_path = './'+image_name+'.png'
        print(image_path)

        if os.path.exists(image_path):
            try:
                with open(image_path, 'rb') as f:
                    image_data = f.read()
                
                self.send_response(200)
                self.send_header('Content-type', 'image/png')  # 이미지 타입에 맞게 수정
                self.end_headers()
                self.wfile.write(image_data)
            except Exception as e:
                self.send_error(500, str(e))
        else:
            self.send_error(404, 'Image not found')

def run(server_class=HTTPServer, handler_class=ImageHandler, port=8000):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    print(f'Starting http server on port {port}...')
    httpd.serve_forever()

if __name__ == '__main__':
    run()
