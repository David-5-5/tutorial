from sklearn.preprocessing import StandardScaler, MinMaxScaler
 
# create data
data = [[11, 2], [3, 7], [0, 10], [11, 8]]
 
# compute required values
scaler = StandardScaler()
model = scaler.fit(data)
scaled_data = model.transform(data)
 
# print scaled data
print(scaled_data)

# scale features
scaler = MinMaxScaler()
model=scaler.fit(data)
scaled_data=model.transform(data)
 
# print scaled features
print(scaled_data)