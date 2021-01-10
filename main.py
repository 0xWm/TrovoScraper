import json

import aiohttp
import requests
from aiohttp import web

routes = web.RouteTableDef()

@routes.post("/GetFollowers")
async def GetFollowers(params):
    content = await params.json(loads=json.loads)

    #check if params exists in request
    if 'params'in content:

        # check if broadcaster_name exists in content['params]
        if 'broadcaster_name' in content['params']:
            broadcaster_name = content['params']['broadcaster_name']
        else:
            return web.json_response({})

         # check if follower_count exists in content['params]
        if 'follower_count' in content['params']:
            follower_count = content["params"]["follower_count"]
        else:
            return web.json_response({})

    else:
        return web.json_response({})

    authorization = ''
    headers = {
    'User-Agent': 'Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:84.0) Gecko/20100101 Firefox/84.0',
    'Accept': '*/*',
    'Accept-Language': 'en-US,en;q=0.5',
    'Content-Type': 'application/json',
    'Origin': 'https://trovo.live',
    'authorization': authorization,
    'Referer': 'https://trovo.live/' + broadcaster_name + '?network=followers',
    'Connection': 'keep-alive',
    'TE': 'Trailers',
    }

    data = '[{"operationName":"getFollowers","variables":{"params":{"uid":100744407,"sort":"Undefined","start":0,"count":' + str(follower_count) + '}},"extensions":{"persistedQuery":{"version":1,"sha256Hash":"fd8f21b163f56c0cca02da33c6e8e6defc4021a594b51caf485363ad26ab9367"},"url":"/' + broadcaster_name + '?network=followers"}}]'

    response = requests.post('https://gql.trovo.live/', headers=headers, data=data)
    json_object = json.loads(response.text)
    received_nicknames = {
        "data": { 
            "nicknames": [
        ]}}
    if json_object:
        #todo: please check for each of this values if they exists in json before using their value
        users = json_object[0]['data']['getFollowers']['list']['users']
        for key in users:
            # Add nickName to nick_names
            nickname = {}
            nickname['nickname'] = key['nickName']
            received_nicknames['data']['nicknames'].append(nickname)
        print(received_nicknames)
    return web.json_response(received_nicknames)

app = web.Application()
app.add_routes(routes)
web.run_app(app)
