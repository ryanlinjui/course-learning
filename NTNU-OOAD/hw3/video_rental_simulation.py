import random  # 匯入 random 模組
from datetime import timedelta, date  # 從 datetime 模組中匯入 timedelta 和 date 類別

# 影片類別和價格的常數
CATEGORIES = {
    "New Release": 5,
    "Drama": 4,
    "Comedy": 3,
    "Romance": 2,
    "Horror": 1
}

# 影片類別
class Video:
    def __init__(self, name, category):
        self.name = name  # 設置影片名稱
        self.category = category  # 設置影片類別

    def __str__(self):
        return f"{self.name} ({self.category})"  # 回傳影片名稱和類別的字串表示

# 顧客類別及其不同類型的子類別
class Customer:
    def __init__(self, name, type):
        self.name = name  # 設置顧客名稱
        self.type = type  # 設置顧客類型

    def create_rental(self, store, date):
        raise NotImplementedError("This method should be implemented by subclasses.")  # 未實作的方法，由子類別實作

class Breezy(Customer):
    def create_rental(self, store, date):
        return store.rent_videos(self, date, random.randint(1, 2), random.randint(1, 2))  # 以隨機數量租借影片

class Hoarder(Customer):
    def create_rental(self, store, date):
        return store.rent_videos(self, date, 3, 7)  # 租借固定數量影片並保留較長時間

class Regular(Customer):
    def create_rental(self, store, date):
        return store.rent_videos(self, date, random.randint(1, 3), random.randint(3, 5))  # 以隨機數量租借影片，租借較長時間

# 租借類別
class Rental:
    def __init__(self, customer, videos, days, start_date):
        self.customer = customer  # 設置租借的顧客
        self.videos = videos  # 設置租借的影片清單
        self.days = days  # 設置租借的天數
        self.start_date = start_date  # 設置租借開始日期
        self.end_date = start_date + timedelta(days=days)  # 設置租借結束日期
        self.total_cost = sum(CATEGORIES[video.category] * days for video in videos)  # 計算總花費

    def __str__(self):
        video_names = ", ".join([video.name for video in self.videos])  # 取得租借的影片名稱列表
        return f"{self.customer.name} rented {video_names} for {self.days} days (${self.total_cost})"  # 回傳租借資訊的字串表示

# 商店類別
class Store:
    def __init__(self):
        self.videos = [Video(f"Video {i+1}", random.choice(list(CATEGORIES.keys()))) for i in range(20)]  # 初始化影片清單
        self.rentals = []  # 初始化租借清單
        self.money_earned = 0  # 初始化收入

    def rent_videos(self, customer, date, num_videos, days):
        if len(self.videos) < num_videos:  # 如果影片清單中的影片數量不足以滿足租借需求
            return None
        selected_videos = random.sample(self.videos, num_videos)  # 從影片清單中隨機選擇影片
        rental = Rental(customer, selected_videos, days, date)  # 建立租借物件
        self.rentals.append(rental)  # 將租借加入租借清單
        self.money_earned += rental.total_cost  # 更新收入
        for video in selected_videos:
            self.videos.remove(video)  # 從影片清單中移除已租借的影片
        return rental  # 回傳租借物件

    def return_videos(self):
        today = date.today()  # 取得今天日期
        for rental in list(self.rentals):
            if rental.end_date <= today:  # 如果租借結束日期早於或等於今天
                self.videos.extend(rental.videos)  # 將影片加回影片清單
                self.rentals.remove(rental)  # 從租借清單中移除該租借

    def report(self):
        print("Current Inventory:")  # 印出目前庫存
        for video in self.videos:
            print(video)
        print(f"Total Money Earned: ${self.money_earned}")  # 印出總收入
        print("Completed Rentals:")  # 印出已完成租借清單
        for rental in self.rentals:
            print(rental)

# 模擬商店運作 35 天
def simulate():
    store = Store()  # 建立商店物件
    customers = [Breezy(f"Customer {i}", "Breezy") for i in range(3)] + \
                [Hoarder(f"Customer {i+3}", "Hoarder") for i in range(3)] + \
                [Regular(f"Customer {i+6}", "Regular") for i in range(4)]  # 建立顧客清單

    today = date.today()  # 取得今天日期
    for day in range(35):  # 進行 35 天的模擬
        store.return_videos()  # 檢查是否有影片應該歸還
        print(f"Day {day+1}:")  # 印出目前模擬的天數
        if store.videos:  # 如果商店有影片庫存
            num_customers = random.randint(1, min(3, len(store.videos)))  # 隨機決定租借影片的顧客數量
            for _ in range(num_customers):  # 依照顧客數量進行租借
                customer = random.choice(customers)  # 隨機選擇一位顧客
                store.rent_videos(customer, today + timedelta(days=day), random.randint(1, min(3, len(store.videos))), random.randint(1, 7))  # 租借影片
        store.report()  # 印出商店報告

simulate()  # 執行模擬
