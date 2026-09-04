#!/usr/bin/env python3
import random

def generate_valid_ticket(city_pool, min_len=2, max_len=10):
    """Generates a ticket with random price and distinct adjacent cities."""
    length = random.randint(min_len, max_len)
    price = random.randint(30, 300) * 5  # Realistic prices like 150, 240, 450
    
    cities = [random.choice(city_pool)]
    while len(cities) < length:
        nxt = random.choice(city_pool)
        if nxt != cities[-1]:  # Adjacent cities must be distinct
            cities.append(nxt)
            
    return price, cities

def generate_connected_case():
    """Generates a fully connected set of tickets and solvable itineraries."""
    # 1. Pick a pool of realistic arbitrary city IDs
    all_possible_cities = [1, 2, 3, 5, 8, 10, 15, 20, 42, 100, 250, 500, 1000, 1500, 2000, 3000, 4000, 5000]
    num_cities = random.randint(5, 10)
    city_pool = random.sample(all_possible_cities, num_cities)
    
    tickets = []
    
    # 2. Add a Backbone Ring to GUARANTEE that all cities are reachable
    # (Ensures problem rule: "Each trip will be possible")
    for i in range(num_cities):
        u = city_pool[i]
        v = city_pool[(i + 1) % num_cities]
        cost = random.randint(50, 150)
        tickets.append((cost, [u, v]))
        
    # 3. Add random multi-leg shortcut tickets (up to NT <= 15)
    extra_tickets_count = random.randint(3, 8)
    for _ in range(extra_tickets_count):
        tickets.append(generate_valid_ticket(city_pool, min_len=2, max_len=10))
        
    random.shuffle(tickets)
    NT = len(tickets)
    
    # 4. Generate random itineraries from the city pool
    NI = random.randint(2, 10)
    itineraries = []
    for _ in range(NI):
        k = random.randint(2, 10)
        itin = [random.choice(city_pool)]
        while len(itin) < k:
            nxt = random.choice(city_pool)
            if nxt != itin[-1]:
                itin.append(nxt)
        itineraries.append(itin)
        
    return NT, tickets, NI, itineraries

def main():
    NUM_CASES = 1  # Number of test cases to generate
    
    for _ in range(NUM_CASES):
        NT, tickets, NI, itineraries = generate_connected_case()
        
        # Print NT
        print(NT)
        
        # Print each ticket: price, m, cities...
        for price, route in tickets:
            print(f"{price} {len(route)} " + " ".join(map(str, route)))
            
        # Print NI
        print(NI)
        
        # Print each itinerary: k, cities...
        for itin in itineraries:
            print(f"{len(itin)} " + " ".join(map(str, itin)))
            
    # Terminate with a single 0
    print(0)

if __name__ == "__main__":
    main()