import requests as r
import time
import copy

#list of reddits
reddits = ['memes', 'comedyheaven', 'gymmemes']

#previous post trackers
lp_comedyheaven = {"data":{"title":"null"}}
lp_gymmemes = {"data":{"title":"null"}}
lp_memes = {"data":{"title":"null"}}


#current reddit post tracker
lp_current = {"data":{"title":"null"}}

while (True):
    #URL for webhook
    hookurl = "https://discord.com/api/webhooks/<your discord webhook url>"

    #reddit auth token
    auth = r.auth.HTTPBasicAuth('<tokenp1>', '<tokenp2>')

    #reddit login info
    data = {'grant_type': 'password',
            'username': '<reddit username>',
            'password': r'<password>'

    #reddit user agent header
    headers = {'User-Agent': 'Memehook_0.0.1'}

    res = r.post('https://www.reddit.com/api/v1/access_token', auth=auth, data=data, headers=headers)

    # convert response to JSON and pull access_token value
    TOKEN = res.json()['access_token']


    # add authorization to our headers dictionary
    headers = {**headers, **{'Authorization': f"bearer {TOKEN}"}}
    # while the token is valid (~2 hours) we just add headers=headers to our requests

    #repeat process for each reddit
    for reddit in reddits:
        #set lp_current to current reddits post
        if reddit=="memes":
            lp_current=copy.copy(lp_memes)
        elif reddit=="comedyheaven":
            lp_current=copy.copy(lp_comedyheaven)
        elif reddit=="gymmemes":
            lp_current=copy.copy(lp_gymmemes)
        
        #get requested reddit posts
        res = r.get(f"https://oauth.reddit.com/r/{reddit}/new", headers=headers, params={'limit': 1})

        post = res.json()['data']['children'][0]
        # debugs
        # print(post['data']['url'])
        # print(post['data']['title'])
        # print(post['data']['subreddit'])



        #if no new post pass
        if lp_current['data']['title'] == post['data']['title']:
            print("is old")
            pass

        else:
            #if new post set previous post
            if reddit=="memes":
                lp_memes=copy.copy(post)
            elif reddit=="comedyheaven":
                lp_comedyheaven=copy.copy(post)
            elif reddit=="gymmemes":
                lp_gymmemes=copy.copy(post)
            print("is new")

            #create json package
            load = {
            "embeds": [{
                "title" : post['data']['title'],
                "url" : post['data']['url'],
                "description" : post['data']['subreddit'],
                "image": {
                "url": post['data']['url']
                }
            }]
            }
            #post json package
            r.post(hookurl, json=load)
    time.sleep(300)
        
