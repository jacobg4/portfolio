from dataclasses import dataclass, field
from account import Account
@dataclass
class Profile:
    accounts: list[Account] = field(default_factory=list)
    total_balance: float = 0.0
    total_limit: float = 0.0
    total_utilization: float = 0.0
    highest_apr_accounts: list[Account] = field(default_factory=list)
    lowest_apr_accounts: list[Account] = field(default_factory=list)
    highest_utilization_accounts: list[Account] = field(default_factory=list)
    available_extra_payment: float = 0.0

@dataclass
class StrategyMinPayment:
    months: int = 0
    interest_paid: float = 0.0
    total_paid: float = 0.0
    interest_saved: float = 0.0
    paid_accounts: list[Account] = field(default_factory=list)

@dataclass
class AvalancheStrategy:
    months: int = 0
    interest_paid: float = 0.0
    total_paid: float = 0.0
    interest_saved: float = 0.0
    paid_accounts: list[Account] = field(default_factory=list)

@dataclass
class SnowballStrategy:
    months: int = 0
    interest_paid: float = 0.0
    interest_saved: float = 0.0
    total_paid: float = 0.0
    paid_accounts: list[Account] = field(default_factory=list)

@dataclass
class HighestBalanceStrategy:
    months: int = 0
    interest_paid: float = 0.0
    total_paid: float = 0.0
    interest_saved: float = 0.0
    paid_accounts: list[Account] = field(default_factory=list)