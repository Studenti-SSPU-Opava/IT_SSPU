from flask_wtf import FlaskForm
from wtforms import StringField, EmailField, DateField, TextAreaField, SubmitField, HiddenField
from wtforms.validators import DataRequired, Email, Length, Optional, ValidationError

class UserForm(FlaskForm):
    """Formulář pro vytvoření a editaci uživatele."""
    username = StringField(
        'Uživatelské jméno',
        validators=[
            DataRequired(message='Uživatelské jméno je povinné'),
            Length(min=3, max=80, message='Uživatelské jméno musí mít 3-80 znaků')
        ],
        render_kw={'placeholder': 'Zadejte uživatelské jméno'}
    )
    
    email = EmailField(
        'Email',
        validators=[
            DataRequired(message='Email je povinný'),
            Email(message='Zadejte platný email'),
            Length(max=120, message='Email nesmí být delší než 120 znaků')
        ],
        render_kw={'placeholder': 'Zadejte email adresu'}
    )
    
    datum_narozeni = DateField(
        'Datum narození',
        validators=[Optional()],
        render_kw={'placeholder': 'YYYY-MM-DD'}
    )
    
    submit = SubmitField('Uložit')
    
    def __init__(self, user_id=None, *args, **kwargs):
        super(UserForm, self).__init__(*args, **kwargs)
        self.user_id = user_id
    
    def validate_username(self, field):
        """Validace jedinečnosti uživatelského jména."""
        from app import User  # Import zde kvůli cyklickému importu
        user = User.query.filter_by(username=field.data).first()
        if user and (self.user_id is None or user.id != self.user_id):
            raise ValidationError('Uživatel s tímto jménem již existuje')
    
    def validate_email(self, field):
        """Validace jedinečnosti emailu."""
        from app import User  # Import zde kvůli cyklickému importu
        user = User.query.filter_by(email=field.data).first()
        if user and (self.user_id is None or user.id != self.user_id):
            raise ValidationError('Uživatel s tímto emailem již existuje')

class CreateUserForm(UserForm):
    """Formulář pro vytvoření nového uživatele."""
    submit = SubmitField('Přidat uživatele')

class EditUserForm(UserForm):
    """Formulář pro editaci existujícího uživatele."""
    submit = SubmitField('Uložit změny')

class PostForm(FlaskForm):
    """Formulář pro vytvoření a editaci příspěvku."""
    title = StringField(
        'Název',
        validators=[
            DataRequired(message='Název je povinný'),
            Length(min=5, max=100, message='Název musí mít 5-100 znaků')
        ],
        render_kw={'placeholder': 'Zadejte název příspěvku'}
    )
    
    content = TextAreaField(
        'Obsah',
        validators=[
            DataRequired(message='Obsah je povinný'),
            Length(min=10, message='Obsah musí mít alespoň 10 znaků')
        ],
        render_kw={
            'placeholder': 'Zadejte obsah příspěvku...',
            'rows': 8
        }
    )
    
    submit = SubmitField('Publikovat')

class DeleteForm(FlaskForm):
    """Formulář pro potvrzení smazání (pouze CSRF token)."""
    submit = SubmitField('Smazat')
