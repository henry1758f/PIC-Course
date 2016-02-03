# PIC-Course
高應大電機系 微處理機課程作業系列 林世允 講師

NKUAS Department of Electric Engineering ,Microcontroller course Homework Series ,Instructor:S.Y.Lin

使用dsPIC33FJ256MC710的16bitMCU開發版學習

Using 16bits DSP(dsPIC33FJ256MC710) development board

## mcu_12_7  /2015/11/25
SPI
透過SPI存取開發版上的RTC "DS3234"
  - [ ] 確認 Real Time Clock IC 正常動作
  - [ ] SPI Driver 是否正確(Mode, Clock)
  - [ ] 找到正確的 SPI chip select
  - [ ] 檢查讀入值符合 DS3234 Datasheet 說明
  - [ ] DS3234 是用 BCD 存取
  - [ ] 完成所需要的 DS3234 RTC API 
  - [ ] 可使用鍵盤設定年、月、日(雙數組)
## mcu_12_6  /2015/11/25
正弦波產生器
  - [x] 動態調整PWM Duty Cycle
  - [ ] RC濾波後輸出正弦波
  - [ ] 頻率由可變電組調整
  - [ ] 正弦波頻率範圍20~50 Hz
  - [ ] 經過放大可使弦波 Vpp 超過 3.3V
  - [ ] 經過箝位電路可以有正負輸出
  - [x] 使用自己的硬體驗收

## mcu_12_5  /2015/11/06
PWM控制

作者為Lilyo

## mcu_12_4  /2015/10/16
ADC作業
目前正在努力達成ADC1的部分!
#####目前程序似乎有問題，ADC看起來並未被開啟，請幫我檢查暫存器設定，或其他有可能的錯誤。
### ADC1
  - [ ] 10 bit mode, 4 channels               10位元解析度模式，4個ADC通道
  - [ ] Simultaneous sample                   要同步採樣
  - [ ] manual conversion                     要手動採樣、手動轉換
  - [ ] Read AN3, AN4, AN5, AN6 pins          讀取AN3、AN4、AN5、AN6腳位
  - [ ] Display result on LCD                 顯示ADC結果在LCD上面
  - [ ] Digital filter is necessary           必須要做數位濾波處理

### ADC2  因應作業繳交期限，先修改老師的程式繳交 mcu12_4_2 (作者Lilyo)
  - [x] 12 bits mode, 1 channel               12位元解析模式，1個ADC通道
  - [x] Manual sample, Automatic conversion   要手動採樣、自動轉換
  - [x] Read AN12, AN13, AN14, AN15 pins      讀取AN12、AN13、AN14、AN15腳位
  - [x] Display result on LCD                 顯示ADC結果在LCD上面
  - [x] Digital filter is necessary           必須要做數位濾波處理

### 自行添加
  - [ ] Nope!

###最後結果
  ADC數值錯誤。

## mcu_12_3  /2015/10/02
使用 LCD 與 Keypad 撰寫計算機
LCD Layout:
  - [x] L1: 第一組數字 
  - [x] L2: 運算元
  - [x] L3: 第二組數字
  - [x] L4: 運算結果
  
按鍵配置:
  - [x] 0~9:0~9,
  - [x] A: +,
  - [x] B: -,
  - [x] E: *,
  - [x] F: /
  - [x] C: Clear 按下後清除畫面並將游標退回 home
  - [x] D: =
  
其他功能要求:
  - [x] 支援正負號，數字範圍(至少)為八位(-99999999 ~ 99999999)
  - [x] 一組運算完成後若直接按運算元(+, -, *, /)則將上一回結果當作此回第一組數字，並執行該運算元之運算
  - [x] 按下一次只能輸出一個數字
  - 
  
自行添加:
  - [ ] 除法取餘數
  - [x] 判斷運算錯誤

