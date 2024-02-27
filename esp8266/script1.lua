station_cfg={}
station_cfg.ssid="Vodafone-Jef"
station_cfg.pwd="Demone38!?"
station_cfg.save = false
wifi.sta.config(station_cfg)

mqtt = mqtt.Client(node.chipid(), 120, "", "")

mqtt:on("connect", function(con) print ("connected") end)
mqtt:on("offline", function(con) print ("offline") end)