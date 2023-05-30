# This Python file uses the following encoding: utf-8

import requests
import pandas as pd

import json

f = open('city.json', mode='r', encoding='utf-8')
text = f.read()
city_json = json.loads(text)
while True:
    from_station = input('请输入你出发的城市： ')
    to_station = input('请输入你达到的城市： ')
    train_date = input('请输入乘车时间(2021-09-08/年-月-日)：')
    url = 'https://kyfw.12306.cn/otn/leftTicket/query'
    data = {
        'leftTicketDTO.train_date': train_date,
        'leftTicketDTO.from_station': city_json[from_station],
        'leftTicketDTO.to_station': city_json[to_station],
        'purpose_codes': 'ADULT',
    }
    headers = {
        'Cookie': '_uab_collina=163108019860709243490927; JSESSIONID=3A879F34238B594124705B10D7C0B0E6; BIGipServerotn=3956736266.64545.0000; guidesStatus=off; highContrastMode=defaltMode; cursorStatus=off; BIGipServerpassport=870842634.50215.0000; RAIL_EXPIRATION=1631354049020; RAIL_DEVICEID=jY49UGp1PWZZ0cY6CWj2wmKFDH60qsPXbu7L4D2DjNDJSM4sbqZmmlUm62-6L3k9SNtBAUgBPn7Rh1-FAxka97-nHNpT3QIh5YIXtw3mGao0mjLNkIv2ayvwqxWyFhdbos5_ziUA3XVil7awDZ0EjzKBAWdl22Hu; route=495c805987d0f5c8c84b14f60212447d; _jc_save_fromStation=%u957F%u6C99%2CCSQ; _jc_save_fromDate=2021-09-08; _jc_save_toDate=2021-09-08; _jc_save_wfdc_flag=dc; _jc_save_toStation=%u5CB3%u9633%u4E1C%2CYIQ',
        # 'Host': 'kyfw.12306.cn',
        # 'Referer': 'https://kyfw.12306.cn/otn/leftTicket/init?linktypeid=dc&fs=%E9%95%BF%E6%B2%99,CSQ&ts=%E5%B2%B3%E9%98%B3%E4%B8%9C,YIQ&date=2021-09-08&flag=N,N,Y',
        'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/91.0.4472.124 Safari/537.36'
    }
    response = requests.get(url=url, params=data, headers=headers)
    response.encoding = response.apparent_encoding
    result = response.json()['data']['result']
    lis = []
    for index in result:
        # requests.utils.unquote(index)
        index_list = index.replace('有', 'Yes').replace('无', 'No').split('|')
        # print(index_list)
        train_number = index_list[3]  # 车次
        if 'G' in train_number:
            time_1 = index_list[8]  # 出发时间
            time_2 = index_list[9]  # 到达时间
            prince_seat = index_list[32]  # 特等座
            first_class_seat = index_list[31]  # 一等座
            second_class = index_list[30]  # 二等座
            dit = {
                'Num': train_number,
                'Start': time_1,
                'End': time_2,
                'Top': prince_seat,
                'First': prince_seat,
                'Second': second_class,
                'Yz': '-',
                'Wz': '-',
                'Rw': '-',
                'Yw': '-',
            }
        else:
            time_1 = index_list[8]  # 出发时间
            time_2 = index_list[9]  # 到达时间
            hard_seat = index_list[29]  # 硬座
            no_seat = index_list[26]  # 无座
            soft_sleeper = index_list[23]  # 软卧
            hard_sleeper = index_list[28]  # 硬卧
            dit = {
                'Num': train_number,
                'Start': time_1,
                'End': time_2,
                'Top': '-',
                'First': '-',
                'Second': '-',
                'Yz': hard_seat,
                'Wz': no_seat,
                'Rw': soft_sleeper,
                'Yw': hard_sleeper,
            }
        lis.append(dit)
    pd.set_option('display.max_rows', None)
    content = pd.DataFrame(lis)
    print(content)
    again = input('是否继续查询(Y/N): ')
    if again == 'Y' or again == 'y':
        continue
    else:
        break
