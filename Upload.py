import boto3
import os

from paramiko import SSHClient
from scp import SCPClient

print "Uploading index.html"

project = os.environ['PROJECT_NAME']
version = 'v' + os.environ['PROJECT_VERSION']

ssh = SSHClient()
ssh.load_system_host_keys()
ssh.connect('stormbrewers.com', 22, 'rengowrath', 'p83EzEYu!')
scp = SCPClient(ssh.get_transport())

scp.put("index.html", "~/public_html/" + project + "/" + version)
scp.close()

s3 = boto3.resource('s3')
b = s3.Bucket('static-content-www')

def uploadFileToS3(file_name):
    print "Uploading file " + file_name 
    data = open(file_name, 'rb')
    b.put_object(ACL='public-read', Key=project + '/' + version + '/' + file_name, Body=data, CacheControl='max-age=31536000, public')
    print "Completed"

uploadFileToS3("ClientExe.data")
uploadFileToS3("ClientExe.js")
uploadFileToS3("ClientExe.wasm")


