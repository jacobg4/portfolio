from dataclasses import dataclass

@dataclass
class Account:
    account_name: str
    balance: float
    limit: float
    apr: float
    minimum_payment: float
