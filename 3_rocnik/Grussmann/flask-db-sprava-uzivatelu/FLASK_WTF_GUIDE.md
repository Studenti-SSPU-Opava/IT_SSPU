# Flask-WTF Formuláře - Dokumentace

## 🔧 Implementované změny

### 1. **Nainstalované balíčky**
- `flask-wtf` - Flask integrace pro WTForms
- `wtforms` - Knihovna pro formuláře

### 2. **Vytvořené soubory**
- `forms.py` - Definice formulářů s validací

### 3. **Aktualizované soubory**
- `app.py` - Upravené route pro práci s formuláři
- `templates/create_user.html` - WTF formulář s validací
- `templates/edit_user.html` - WTF formulář s validací  
- `templates/users.html` - CSRF token pro mazání
- `static/css/style.css` - Styly pro validaci

## 📋 Definované formuláře

### **UserForm** (základní třída)
```python
class UserForm(FlaskForm):
    username = StringField(validators=[DataRequired(), Length(3-80)])
    email = EmailField(validators=[DataRequired(), Email(), Length(max=120)])
    datum_narozeni = DateField(validators=[Optional()])
    
    def validate_username(self, field):  # Vlastní validace
    def validate_email(self, field):     # Vlastní validace
```

### **CreateUserForm** - pro vytváření
```python
class CreateUserForm(UserForm):
    submit = SubmitField('Přidat uživatele')
```

### **EditUserForm** - pro editaci
```python
class EditUserForm(UserForm):
    submit = SubmitField('Uložit změny')
```

### **DeleteForm** - CSRF ochrana pro mazání
```python
class DeleteForm(FlaskForm):
    submit = SubmitField('Smazat')
```

## ✅ Výhody Flask-WTF

### **Bezpečnost**
- ✅ **CSRF ochrana** - automatický token pro všechny formuláře
- ✅ **XSS ochrana** - automatické escapování hodnot
- ✅ **Validace na serveru** - ověření dat před zpracováním

### **Validace**
- ✅ **Vestavěné validátory** - DataRequired, Email, Length, Optional
- ✅ **Vlastní validátory** - validate_username(), validate_email()
- ✅ **Automatické chybové zprávy** - v češtině
- ✅ **Kontrola jedinečnosti** - username a email

### **Uživatelské rozhraní**
- ✅ **Automatické renderování** - {% raw %}{{ form.field() }}{% endraw %}
- ✅ **Styling CSS tříd** - .is-invalid pro chyby
- ✅ **Zobrazení chyb** - {% raw %}{% for error in form.field.errors %}{% endraw %}
- ✅ **Zachování hodnot** - při chybě se formulář nevymaže

### **Zjednodušený kód**
- ✅ **Méně kódu** - 15 řádků místo 35 v route
- ✅ **Centralizovaná validace** - vše v forms.py
- ✅ **Automatická konverze** - DateField automaticky parsuje datum
- ✅ **Typ safety** - EmailField, DateField

## 🔄 Porovnání před/po

### **Před (manuální formuláře)**
```python
@app.route('/users/create', methods=['POST'])
def create_user_form():
    username = request.form.get('username')
    email = request.form.get('email')
    datum_narozeni_str = request.form.get('datum_narozeni')
    
    # Ruční validace
    if not username or not email:
        flash('Chyba...', 'error')
        return render_template('create_user.html')
    
    # Kontrola jedinečnosti
    if User.query.filter_by(username=username).first():
        flash('Uživatel již existuje', 'error')
        return render_template('create_user.html')
    
    # Parsování data
    datum_narozeni = None
    if datum_narozeni_str:
        try:
            datum_narozeni = datetime.strptime(datum_narozeni_str, '%Y-%m-%d').date()
        except ValueError:
            flash('Špatný formát data', 'error')
            return render_template('create_user.html')
    
    # Vytvoření uživatele...
```

### **Po (Flask-WTF)**
```python
@app.route('/users/create', methods=['POST'])
def create_user_form():
    form = CreateUserForm()
    
    if form.validate_on_submit():
        user = User(
            username=form.username.data,
            email=form.email.data,
            datum_narozeni=form.datum_narozeni.data
        )
        db.session.add(user)
        db.session.commit()
        
        flash(f'Uživatel {form.username.data} byl vytvořen', 'success')
        return redirect(url_for('list_users'))
    
    return render_template('create_user.html', form=form)
```

## 🎯 Testování

### **Test validace**
1. **Prázdné pole** - "Uživatelské jméno je povinné"
2. **Krátké jméno** - "Uživatelské jméno musí mít 3-80 znaků"
3. **Neplatný email** - "Zadejte platný email"
4. **Duplicitní username** - "Uživatel s tímto jménem již existuje"
5. **Duplicitní email** - "Uživatel s tímto emailem již existuje"

### **Test CSRF**
1. Formulář bez tokenu - 400 Bad Request
2. Neplatný token - 400 Bad Request
3. Platný token - úspěšné zpracování

## 🚀 Spuštění

```bash
# Aktivace prostředí
source .venv/bin/activate

# Spuštění aplikace
flask run --port 5001

# Otevření v prohlížeči
http://127.0.0.1:5001/users/create
```

Aplikace nyní používá moderní, bezpečné a validované formuláře s Flask-WTF! 🎉
