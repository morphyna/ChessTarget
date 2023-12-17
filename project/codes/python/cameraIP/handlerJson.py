import requests
import time

#url = http://192.168.1.5/status
# new_mode toma un valor entre 0 y 2
# 0 : esperando orden
# 1 : loop take some photos
# 2 : object rocognition

def handlerJson(url, new_mode):
    mode = 0
    state = 0
    posCapture = 0
    servos = [0,0,0,0]
    try:
        response = requests.get(url)
        if response.status_code == 200:
            status_json = response.json()

            mode = status_json.get('mode', None)
            state = status_json.get('state', None)
            posCapture = status_json.get('posCapture', None)
            servos = status_json.get('servos', {})

            print("Estado actual:")
            print(f"Mode: {mode}")
            print(f"State: {state}")
            print(f"posCapture: {posCapture}")            
            print("Servos:", list(servos.values()))

            if state == 0:
                status_json['mode'] = new_mode
                response = requests.post(url, json=status_json)

                if response.status_code == 200:
                    print("Solicitud POST exitosa.")
                else:
                    print(f"Error en la solicitud POST. Código de estado: \
                            {response.status_code}")
                    
            time.sleep(0.01)

        else:
            print(f"Error en la solicitud GET. Código de estado: \
                {url}: {response.status_code}")

    except Exception as e:
        print(f"Error: {e}")
        
    return mode, state, posCapture, servos
