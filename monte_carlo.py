import random
import numpy as np

# Define constants
months = 24
initial_customers = 518  # Starting with 1000 customers
salary = 100000  # Monthly salary cost
churn_rate_range = (0.2, 0.8)  # Customers leaving each month (between 20% and 80%)
growth_prob = 0.9  # 90% probability of customer base growth
growth_rate = 0.1  # Growth rate of customer base
transaction_value_range = (100, 100_000_000)  # Amount of money customers put through the system
interest_rate_range = (0.005, 0.01)  # Interest rate earned on transactions (0.5% to 1%)
startup_cache = -2_200_000

# Monte Carlo Simulation
n_simulations = 10000  # Number of simulations
total_revenue = []

for _ in range(n_simulations):
    customers = initial_customers
    revenue = startup_cache
    for month in range(months):
        # Apply churn rate (customers leaving the system)
        churn_rate = random.uniform(*churn_rate_range)
        customers = int(customers * (1 - churn_rate))
        
        # Apply growth if probability allows
        if random.random() < growth_prob:
            customers = int(customers * (1 + growth_rate))
        
        # Calculate the transaction value for the remaining customers
        total_transaction_value = sum([random.uniform(*transaction_value_range) for _ in range(customers)])
        
        # Apply interest rate to calculate revenue
        interest_rate = random.uniform(*interest_rate_range)
        monthly_revenue = total_transaction_value * interest_rate
        
        # Subtract monthly salary cost
        monthly_revenue -= salary
        
        # Add to the total revenue for the startup
        revenue += monthly_revenue
    
    # Store the total revenue for this simulation
    total_revenue.append(revenue)

# Analyze the results
average_revenue = np.mean(total_revenue)
success_prob = np.sum(np.array(total_revenue) > 0) / n_simulations

print(f"Average Revenue After {months} Months: ${average_revenue:,.2f}")
print(f"Probability of Success (Revenue > 0): {success_prob * 100:.2f}%")