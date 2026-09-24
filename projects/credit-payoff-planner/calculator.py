def utilization(balance, limit):
    return balance / limit

def monthly_apr(apr):
    return apr/100/12

def paydown(balance, payment):
    return balance - payment

def monthly_interest(balance, mapr):
    return balance * mapr