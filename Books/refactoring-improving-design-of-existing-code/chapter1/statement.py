from create_statement_data import create_statement_data


def render_plain_text(data):
    result = f"Statement for {data['customer']}\n"

    for perf in data['performances']:
        result += f"    {perf['play']['name']}: ${usd(perf['amount'] / 100)} ({perf['audience']} seats)\n"

    result += f"Amount owned is ${usd(data['total_amount'] / 100)}\n"
    result += f"You earned {data['total_volume_credits']} credits\n"
    return result


def statement(invoice, plays):
    return render_plain_text(create_statement_data(invoice, plays))


def html_statement(invoice, plays):
    return render_html(create_statement_data(invoice, plays))


def render_html(data):
    result = f"<h1>Statement for {data['customer']}</h1>\n"
    result += "<table>\n"
    result += "<tr><th>play</th></tr><th>seats</th><th>cost</th></tr>"
    for perf in data['performances']:
        result += f"<tr><td>${perf['play']['name']}</td><td${perf['audience']}</td>"
        result += f"<td>${usd(perf['amount'] / 100)}</td></tr>\n"
    result += "</table>\n"
    result += f"<p>Amount owned is <em>${usd(data['total_amount'] / 100)}</em></p>\n"
    result += f"<p>You earned <em>{data['total_volume_credits']}</em> credits</p>\n"
    return result


def usd(number):
    return f"${number:.2f}$"


