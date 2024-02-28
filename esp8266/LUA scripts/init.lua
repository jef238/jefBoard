wifi.setmode(wifi.SOFTAP)
cfg={}
cfg.ssid="jefBoard"
wifi.ap.config(cfg)

uart.setup(0, 9600, 8, uart.PARITY_NONE, uart.STOPBITS_1, 1)

sv = net.createServer(net.TCP, 30)

function receiver(sck, data)
  print(data)  
end

if sv then
  sv:listen(8080, function(conn)
    conn:on("receive", receiver)    
  end)
end

