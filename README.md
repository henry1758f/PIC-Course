# PIC-Course
高應大電機系 微處理機課程作業系列 林世允 講師

NKUAS Department of Electric Engineering ,Microcontroller course Homework Series ,Instructor:S.Y.Lin

使用dsPIC33FJ256MC710的16bitMCU開發版學習

Using 16bits DSP(dsPIC33FJ256MC710) development board

## mcu_12_3  /2015/10/02
使用 LCD 與 Keypad 撰寫計算機
LCD Layout:
  - [x] L1: 第一組數字 
<<<<<<< HEAD
  - [x] L2: 運算元
  - [x] L3: 第二組數字
  - [x] L4: 運算結果
=======
  - [ ] L2: 運算元
  - [ ] L3: 第二組數字
  - [ ] L4: 運算結果
>>>>>>> refs/remotes/origin/master
  
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
<<<<<<< HEAD
  - [ ] 一組運算完成後若直接按運算元(+, -, *, /)則將上一回結果當作此回第一組數字，並執行該運算元之運算
  - [x] 按下一次只能輸出一個數字
自行添加:
  - [ ] 除法取餘數
  - [x] 判斷運算錯誤
=======
  - [ ] 一組運算完成後若直接按運算元(+, -, *, /)則將上一回結果當作此
  - [ ] 回第一組數字，並執行該運算元之運算
  - [x] 按下一次只能輸出一個數字
自行添加:
  - [ ] 除法取餘數
  - [x] 輸入溢位判斷
>>>>>>> refs/remotes/origin/master
