import json
import os
import glob
dic = {
    "name": "Magical Cats",
    "timeLimit": 2.5,
    "hasSpecialJudge": False,
    "testdata": []
}

ps = [0,5,10,35,50]
for p in ps:
    dic['testdata'].append({'points': p , 'tests':[]})

for fn in glob.glob('tests/*.in'):
    fn = os.path.basename(fn)
    # print(fn)
    g , idx = fn.split('-')
    dic['testdata'][int(g)]['tests'].append(fn[:-3])
    if int(g) in [0,1,2,3]:
        dic['testdata'][int(4)]['tests'].append(fn[:-3])
    if int(g) == 0:
        dic['testdata'][int(1)]['tests'].append(fn[:-3])
for ts in dic['testdata']:
    ts['tests'].sort()
with open('meta.json' , 'w') as f:
    print(json.dumps(dic , indent=4) , file = f)