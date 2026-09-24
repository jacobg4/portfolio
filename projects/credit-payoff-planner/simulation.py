import copy
from calculator import *

def minimum_payment_simulation(original_profile):
    profile = copy.deepcopy(original_profile)
    months = 0
    interest_paid = float(0.0)
    total_paid = float(0.0)
    while profile.total_balance > 0:
        for account in profile.accounts:
            if account.balance > 0:
                interest = monthly_interest(account.balance, monthly_apr(account.apr))
                interest_paid += interest
                account.balance += interest

                if account.balance > 0 + account.minimum_payment:
                    account.balance = paydown(account.balance, account.minimum_payment)
                    total_paid += account.minimum_payment
                else:
                    total_paid += account.balance
                    account.balance = paydown(account.balance, account.balance)


        months += 1
        profile.total_balance = sum(
            account.balance for account in profile.accounts
        )
    return months, interest_paid, total_paid

def payoff_strategy(accounts, sort_key, reverse=False, extra_payment=0):
    sorted_accounts = sorted(accounts, key=sort_key, reverse=reverse)
    paid_accounts = []
    months = 0
    interest_paid: float = 0.0
    total_paid: float = 0.0
    total_balance = sum(
        account.balance for account in sorted_accounts
    )
    while total_balance > 0:
        for account in sorted_accounts:
            if account.balance > 0:
                if account == sorted_accounts[0]:
                    interest = monthly_interest(account.balance, monthly_apr(account.apr))
                    interest_paid += interest
                    account.balance += interest

                    if account.balance > 0 + account.minimum_payment + extra_payment:
                        total_payment = account.minimum_payment + extra_payment
                        account.balance = paydown(account.balance, total_payment)
                        total_paid += account.minimum_payment + extra_payment
                    else:
                        total_paid += account.balance
                        account.balance = paydown(account.balance, account.balance)
                        paid_accounts.append({
                            "account": account,
                            "months_to_payoff": months +1
                        })
                        sorted_accounts.remove(account)
                else:
                    interest = monthly_interest(account.balance, monthly_apr(account.apr))
                    interest_paid += interest
                    account.balance += interest

                    if account.balance > 0 + account.minimum_payment:
                        account.balance = paydown(account.balance, account.minimum_payment)
                        total_paid += account.minimum_payment
                    else:
                        total_paid += account.balance
                        account.balance = paydown(account.balance, account.balance)

        months += 1
        total_balance = sum(
            account.balance for account in sorted_accounts
        )
    return months, interest_paid, total_paid, paid_accounts