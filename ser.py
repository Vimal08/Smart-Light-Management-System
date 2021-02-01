import serial
import time
import smtplib
from email.message import EmailMessage
from pubnub.pnconfiguration import PNConfiguration
from pubnub.pubnub import PubNub

pnconfig = PNConfiguration()
pnconfig.subscribe_key = "sub-c-cc7608da-0d5d-11eb-8c41-4e9374a468c8"
pnconfig.publish_key = "pub-c-bd3b7133-39b9-42c4-b134-e78d88d04b3b"
pnconfig.ssl = False
pnconfig.uuid = "Client-2ngm3"
pubnub = PubNub(pnconfig)

msg = EmailMessage()
msg['subject'] = 'SLMS Status Alert'
msg['from'] = "vimalwilliam99@gmail.com"
msg['to'] = 'vimalw@jerusalemengg.ac.in'
msg.add_alternative("""\
<!DOCTYPE html>
<html>
<body>
<h2 style ="background-color:orange;font-family:time new roman">Smart Light Management System </h2>
<p style ="background-color:grey;">
The System Status: On<br></p>
<hr>
<hr>
Regards<br>
SLMS System Admin<br>
</body>
</html>""",subtype='html')

board = serial.Serial("COM3",115200)
while(1):
    var = board.readline()
    var_n = var.decode()
    str = var_n.rstrip()
    print(str)
    from pubnub.exceptions import PubNubException
    try:
        envelope = pubnub.publish().channel("Channel-wccjykjap").message(str).sync()
        print("publish timetoken: %d" % envelope.result.timetoken)
    except PubNubException as e:
        handle_exception(e)
    #time.sleep(1)
    if(int(str)<600):
        #board.write('1'.encode())
        print('System status: ON')
        try:
            server = smtplib.SMTP_SSL("smtp.gmail.com",465)
            server.login('vimalwilliam99@gmail.com','Vimal@2001')
            server.send_message(msg)
            server.quit()
            print("Mail Send....")
            #continue
        except:
            print("Error in process....")
    else:
        #board.write('0'.encode())
        print("System status: Off")
