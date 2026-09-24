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
    while limit <= 0:
        limit = float(input("Limit cannot be less than or equal to 0: "))
    apr = float(input("Enter APR: "))
    minimum_payment = float(input("Enter minimum payment: "))
    interest = monthly_interest(balance, monthly_apr(apr))
    while minimum_payment <= interest:
        minimum_payment = float(input(f"Minimum payment must exceed monthly interest of ${interest:.2f}: "))

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
strategy_avalanche = AvalancheStrategy()
strategy_avalanche.months, strategy_avalanche.interest_paid, strategy_avalanche.total_paid, strategy_avalanche.paid_accounts = payoff_strategy(
    accounts,
    sort_key=lambda acc:acc.apr,
    reverse=True,
    extra_payment=profile.available_extra_payment
)
strategy_snowball = SnowballStrategy()
strategy_snowball.months, strategy_snowball.interest_paid, strategy_snowball.total_paid, strategy_snowball.paid_accounts = payoff_strategy(
    accounts,
    sort_key=lambda acc: acc.balance,
    reverse=False,
    extra_payment=profile.available_extra_payment
)
strategy_highest_balance = HighestBalanceStrategy()
strategy_highest_balance.months, strategy_highest_balance.interest_paid, strategy_highest_balance.total_paid, strategy_highest_balance.paid_accounts = payoff_strategy(
    accounts,
    sort_key=lambda acc: acc.balance,
    reverse=True,
    extra_payment=profile.available_extra_payment
)
strategy_avalanche.interest_saved = strategy_min_payment.interest_paid - strategy_avalanche.interest_paid
strategy_snowball.interest_saved = strategy_min_payment.interest_paid - strategy_snowball.interest_paid
strategy_highest_balance.interest_saved = strategy_min_payment.interest_paid - strategy_highest_balance.interest_paid

report = generate_report(
    strategy_min_payment,
    strategy_avalanche,
    strategy_snowball,
    strategy_highest_balance
)
print(report)
with open("payoff_report.txt", "w", encoding="utf-8") as f:
    f.write(report)


#for i, account in enumerate(accounts):
#    print(f"\nAccount: {i+1}")
#    print(f"Balance: {account.balance}")
#    print(f"Limit: {account.limit}")
#    print(f"APR: {account.apr}")
#    print(f"Minimum payment: {account.minimum_payment}")

