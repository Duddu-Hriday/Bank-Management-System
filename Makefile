CPP = g++
customer: Customer.cpp
	$(CPP) Customer.cpp -o customer
admin: ADMIN.cpp
	$(CPP) ADMIN.cpp -o admin