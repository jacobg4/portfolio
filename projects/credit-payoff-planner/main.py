from profile import *
from account import Account
from simulation import *
from calculator import *
accounts = []

number_of_accounts = 0
while number_of_accounts <= 0:
    number_of_accounts = int(input("Enter the number of accounts: "))

for i in range(number_of_accounts):
    print(f"\nAccount: {i+1}")
    account_name = input("Enter account name: ")
    balance = float(input("Enter balance: "))
    limit = float(input("Enter limit: "))
    apr = float(input("Enter APR: "))
    minimum_payment = float(input("Enter minimum payment: "))

    account = Account(account_name, balance, limit, apr, minimum_payment)

    accounts.append(account)

profile = Profile()

profile.number_of_accounts = len(accounts)

for account in accounts:
    profile.total_balance += account.balance
    profile.total_limit += account.limit
    profile.accounts.append(account)

profile.total_utilization = utilization(profile.total_balance, profile.total_limit)
highest_apr = accounts[0].apr
profile.highest_apr_accounts = [accounts[0]]
lowest_apr = accounts[0].apr
profile.lowest_apr_accounts = [accounts[0]]
profile.highest_utilization_accounts = [accounts[0]]
highest_utilization = utilization(accounts[0].balance, accounts[0].limit)
for account in accounts[1:]:
    #Calculate Highest APR accounts
    if account.apr > highest_apr:
        highest_apr = account.apr
        profile.highest_apr_accounts = [account]
    elif account.apr == highest_apr:
        profile.highest_apr_accounts.append(account)
    # Calculate Lowest APR accounts
    if account.apr < lowest_apr:
        lowest_apr = account.apr
        profile.lowest_apr_accounts = [account]
    elif account.apr == lowest_apr:
        profile.lowest_apr_accounts.append(account)
    # Calculate highest utilization account
    if utilization(account.balance, account.limit) > highest_utilization:
        highest_utilization = utilization(account.balance, account.limit)
        profile.highest_utilization_accounts = [account]
    elif utilization(account.balance, account.limit) == highest_utilization:
        profile.highest_utilization_accounts.append(account)

profile.available_extra_payment = float(input("Enter the available extra payment amount per month: "))

strategy_min_payment = StrategyMinPayment()
strategy_min_payment.months, strategy_min_payment.interest_paid, strategy_min_payment.total_paid = minimum_payment_simulation(profile)

print(f"Months to payoff: {strategy_min_payment.months}")
print(f"Interest paid: ${strategy_min_payment.interest_paid:.2f}")
print(f"Total paid: ${strategy_min_payment.total_paid:.2f}")

for i, account in enumerate(accounts):
    print(f"\nAccount: {i+1}")
    print(f"Balance: {account.balance}")
    print(f"Limit: {account.limit}")
    print(f"APR: {account.apr}")
    print(f"Minimum payment: {account.minimum_payment}")

