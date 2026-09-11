from collections import deque
from typing import List


class RideSharingSystem:

    def __init__(self):
        self.rides = deque()
        self.drivers = deque()
        self.ride_hash = set()

    def addRider(self, riderId: int) -> None:
        self.rides.append(riderId)
        self.ride_hash.add(riderId)

    def addDriver(self, driverId: int) -> None:
        self.drivers.append(driverId)

    def matchDriverWithRider(self) -> List[int]:
        while self.rides and self.rides[0] not in self.ride_hash:
            self.rides.popleft()
        
        if self.rides and self.drivers:
            return [self.drivers.popleft(), self.rides.popleft()]
        else: return [-1, -1]

    def cancelRider(self, riderId: int) -> None:
        if riderId in self.ride_hash: self.ride_hash.remove(riderId)


# Your RideSharingSystem object will be instantiated and called as such:
# obj = RideSharingSystem()
# obj.addRider(riderId)
# obj.addDriver(driverId)
# param_3 = obj.matchDriverWithRider()
# obj.cancelRider(riderId)

# Your RideSharingSystem object will be instantiated and called as such:
# obj = RideSharingSystem()
# obj.addRider(riderId)
# obj.addDriver(driverId)
# param_3 = obj.matchDriverWithRider()
# obj.cancelRider(riderId)