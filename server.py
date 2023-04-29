import subprocess

from flask import Flask, request

app = Flask(__name__)


@app.route("/factor", methods=['POST'])
def factor():
    data = request.get_data(as_text=True)

    output = subprocess.check_output(['Algorithms/cmake-build-debug/bin/Integer_factorization-pollards_rho'], input=data,
                                     text=True)
    # print(output)
    return output


@app.route("/check-primality", methods=['POST'])
def check_primality():
    data = request.get_data(as_text=True)

    output = subprocess.check_output(['Algorithms/cmake-build-debug/bin/Primality_test-miller_rabin'], input=data,
                                     text=True)
    # print(output)
    return output


app.run()
