import copy
from calculator import *
from datetime import datetime
import textwrap

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
    accounts = copy.deepcopy(accounts)
    sorted_accounts = sorted(accounts, key=sort_key, reverse=reverse)
    paid_accounts = []
    months = 0
    interest_paid: float = 0.0
    total_paid: float = 0.0
    total_balance = sum(
        account.balance for account in sorted_accounts
    )
    budget = extra_payment
    while total_balance > 0:
        target_account = next(a for a in sorted_accounts if a.balance > 0)
        for account in sorted_accounts:
            interest = monthly_interest(account.balance, monthly_apr(account.apr))
            interest_paid += interest
            account.balance += interest
        for account in sorted_accounts:
            if account.balance > 0:
                if account.balance > 0 + account.minimum_payment:
                    account.balance = paydown(account.balance, account.minimum_payment)
                    total_paid += account.minimum_payment
                else:
                    total_paid += account.balance
                    budget += account.minimum_payment - account.balance
                    account.balance = paydown(account.balance, account.balance)
                    paid_accounts.append({
                        "account": account,
                        "months_to_payoff": months + 1
                    })
                    extra_payment += account.minimum_payment

        for account in sorted_accounts:
            if account.balance > 0:
                if account == target_account:
                    if account.balance > 0 + budget:
                        account.balance = paydown(account.balance, budget)
                        total_paid += budget
                        budget = 0
                    else:
                        total_paid += account.balance
                        budget -= account.balance
                        account.balance = paydown(account.balance, account.balance)
                        paid_accounts.append({
                            "account": account,
                            "months_to_payoff": months +1
                        })
                        extra_payment += account.minimum_payment

                else:
                    if account.balance > 0 + budget:
                        account.balance = paydown(account.balance, budget)
                        total_paid += budget
                        budget = 0
                    else:
                        total_paid += account.balance
                        budget -= account.balance
                        account.balance = paydown(account.balance, account.balance)
                        paid_accounts.append({
                            "account": account,
                            "months_to_payoff": months + 1
                        })
                        extra_payment += account.minimum_payment


        if target_account.balance == 0:
            sorted_accounts.remove(target_account)
        months += 1
        total_balance = sum(
            account.balance for account in sorted_accounts
        )
        budget = extra_payment
    return months, interest_paid, total_paid, paid_accounts

def generate_report(
    min_payment,
    avalanche,
    snowball,
    highest_balance
):
    generated = datetime.now().strftime("%Y-%m-%d %H:%M")
    LABEL_W = 20
    COL_W = 14
    strategies = [
        ("Minimum Only", min_payment),
        ("Avalanche", avalanche),
        ("Snowball", snowball),
        ("High Balance", highest_balance),
    ]
    width = LABEL_W + COL_W * len(strategies)
    lines = []
    lines.append("Credit Card Payoff Report".center(width))
    lines.append(generated.center(width))
    lines.append("-"*width)
    header = "".ljust(LABEL_W)
    for name, strategy in strategies:
        header += name.rjust(COL_W)
    lines.append(header)
    lines.append("-"*width)
    months_row = "Months".ljust(LABEL_W)
    interest_row = "Interest".ljust(LABEL_W)
    total_row = "Total Paid".ljust(LABEL_W)
    saved_row = "Interest Saved".ljust(LABEL_W)

    for name, strategy in strategies:
        months = strategy.months
        interest = strategy.interest_paid
        total = strategy.total_paid
        saved = strategy.interest_saved

        months_row += str(months).rjust(COL_W)
        interest_row += f"${interest:,.2f}".rjust(COL_W)
        total_row += f"${total:,.2f}".rjust(COL_W)
        saved_row += f"${saved:,.2f}".rjust(COL_W)

    lines.append(months_row)
    lines.append(interest_row)
    lines.append(total_row)
    lines.append(saved_row)
    lines.append("")
    lines.append("Payoff Timeline")
    for name, strategy in strategies[1:]:
        lines.append(f"{name} ({strategy.months} months)")
        for p in strategy.paid_accounts:
            lines.append(f"  Month {p['months_to_payoff']:>3}: {p['account'].account_name} paid off")
    lines.append("*Disclaimer*")
    lines.append(textwrap.fill("This report assumes no additional purchases, cash advances, fees, or other charges are added to the accounts during the payoff period. Any account activity beyond modeled interest may change the projected payoff timeline, total amount paid, and estimated interest savings.", width))
    return "\n".join(lines)