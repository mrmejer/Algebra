import subprocess
from flask import Flask, request
from flask_cors import CORS
from flask_cors import cross_origin

app = Flask(__name__)
cors = CORS(app)


@app.route("/factor", methods=['POST'])
@cross_origin()
def factor():
    data = request.get_data(as_text=True)
    print("factor " + data + "\n")

    output = subprocess.check_output(['Algorithms/cmake-build-debug/bin/Integer_factorization-pollards_rho'], input=data,
                                     text=True)
    print("out:\n" + output)
    return output


@app.route("/check-primality", methods=['POST'])
@cross_origin()
def check_primality():
    data = request.get_data(as_text=True)
    print("test " + data + "\n")

    output = subprocess.check_output(['Algorithms/cmake-build-debug/bin/Primality_test-miller_rabin'], input=data,
                                     text=True)
    print("out:\n" + output)
    return output


if __name__ == '__main__':
    app.run(host='0.0.0.0')