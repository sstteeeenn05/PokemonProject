# How to play
點擊程式"run.bat"執行程式，程式會進行loading後開啟網頁


# Menu:
##  Normal Mode: 可以根據檔案中的Pokemon來進行對戰。
    點擊後出現:
    Manage:選取進行遊戲的寶可夢和技能組
    cancel:退回到Menu
    confirm:開始遊戲

##  Test Mode: 會由測試的指令來進行遊戲。
   依照範例TestCase進行動作，可以檢視每個回合的動作
    Manage: 選取進行遊戲的寶可夢和技能組。
    Test: 測試是否有讀取到圖片。

#Game:
  左上方框:為對手寶可夢資訊
  右下方框:為己方寶可夢資訊
  寶可夢資訊包含:名字，血量，等級，狀態...

#遊戲介面
  玩家寶可夢與敵對寶可夢的對戰
  戰鬥畫面
##  底層的方框:
###    資訊欄:顯示寶可夢執行的動作
        [Turn#]顯示battle/posion/swap等資訊
        [Turn#]顯示敵方動作    

###    按鈕:
        Fight:選擇技能
        Bag:使用道具
        Pokemon:切換寶可夢
        Exit:離開遊戲