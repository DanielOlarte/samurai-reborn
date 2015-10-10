
#include "Stats.h"
#include "GameRender.h"

PlayerStats::Stats::Stats(void)
{
  health.pointsOfLife = 1400;
  health.maxPointsOfLife = 1400;
}

PlayerStats::Stats::~Stats(void)
{	
  delete faces.faces;
  delete health.healthBar;
  delete skullKills;

  health.healthForms.clear();

  glDeleteTextures(1, &textureHealthKills);
}

void PlayerStats::Stats::initializeFaceStates(std::string filename, int idPlayer)
{
  health.healthBar = new Image::ImageObject( Vector2f(170.0f*idPlayer + 125.0f, 8.0f),
                                             Vector2f(29.0f, 100.0f),
                                             Vector2f(3.0f, 0.0f) ); 

  health.healthForms.push_back( Image::ImageHealth( Vector2f(170.0f*idPlayer + 132.0f, 87.0f),
	                                                Vector2f(15.0f, 8.0f),
												    Vector2f(35.0f, 16.0f),
												    1 ) );
  health.healthForms.push_back( Image::ImageHealth( Vector2f(170.0f*idPlayer + 132.0f, 82.0f),
	                                                Vector2f(15.0f, 5.0f),
												    Vector2f(35.0f, 9.0f),
												    13 ) );
  health.healthForms.push_back( Image::ImageHealth( Vector2f(170.0f*idPlayer + 132.0f, 20.0f),
	                                                Vector2f(15.0f, 4.0f),
												    Vector2f(35.0f, 4.0f),
												    1 ) );

  textureHealthKills = GameRender::loadTexture("Resources/UI/HealthBarSkull.png");
  faces.faces = new Image::GameImage( Vector2f( 170.0f*idPlayer + 30.0f, 15.0f ),
	                                  Vector2f( 100.0f, 100.0f ),
									  Vector2f( 0.0f, 0.0f ),
									  filename );
  faces.currentFaceState = 2;
  faces.maxFaces = 3;

  skullKills = new Image::ImageObject( Vector2f( 170.0f*idPlayer + 70.0f, 90.0f ),
	                                   Vector2f( 34.0f, 34.0f ),
									   Vector2f( 67.0f, 0.0f ) );
}

void PlayerStats::Stats::drawFaceState()
{
  GameRender::drawSpriteTexture(faces.faces->getTexture(), faces.faces->getPosition(), faces.currentFaceState,
		                        100.0f, 100.0f);
}

void PlayerStats::Stats::drawSkullKills()
{
  GameRender::drawSpecificTexture(textureHealthKills, skullKills->getPosition(), skullKills->getTexturePosition(),
		                          skullKills->getOffset().x, skullKills->getOffset().y );
}

void PlayerStats::Stats::drawHealthBar()
{
  GLfloat widthTexture, heightTexture;

  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
  glEnableClientState( GL_VERTEX_ARRAY );
  glEnableClientState( GL_TEXTURE_COORD_ARRAY );	

  glBindTexture( GL_TEXTURE_2D, textureHealthKills );

  glGetTexLevelParameterfv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &widthTexture);
  glGetTexLevelParameterfv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &heightTexture);

  Vector2f position = health.healthBar->getPosition();
  Vector2f offset = health.healthBar->getOffset();
  Vector2f texturePosition = health.healthBar->getTexturePosition();

  const GLfloat vertX = position.x;
  const GLfloat vertY = position.y;
  const GLfloat vertOffsetX = offset.x;
  const GLfloat vertOffsetY = offset.y;
    
  const GLfloat verts[] = {
            vertX, vertY,
            vertX + vertOffsetX, vertY,
            vertX + vertOffsetX, vertY + vertOffsetY,
            vertX, vertY + vertOffsetY
  };

  const GLfloat textureX = texturePosition.x / widthTexture;
  const GLfloat textureY = texturePosition.y / heightTexture;
  const GLfloat textureWidth = offset.x / widthTexture;
  const GLfloat textureHeight = offset.y / heightTexture;

  const GLfloat texVerts[] = {
            textureX, textureY,
            textureX + textureWidth, textureY,
            textureX + textureWidth, textureY + textureHeight,
            textureX, textureY + textureHeight
  };
            
  glVertexPointer(2, GL_FLOAT, 0, verts);
  glTexCoordPointer(2, GL_FLOAT, 0, texVerts);
  glDrawArrays(GL_QUADS, 0, 4);

  glDisableClientState( GL_VERTEX_ARRAY );			
  glDisableClientState( GL_TEXTURE_COORD_ARRAY );	
}

void PlayerStats::Stats::drawHealth()
{
  GLfloat widthTexture, heightTexture;

  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
  glEnableClientState( GL_VERTEX_ARRAY );
  glEnableClientState( GL_TEXTURE_COORD_ARRAY );	

  glBindTexture( GL_TEXTURE_2D, textureHealthKills );

  glGetTexLevelParameterfv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &widthTexture);
  glGetTexLevelParameterfv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &heightTexture);

  if ( health.pointsOfLife <= 0 )
  {
	return;
  }

  for (std::string::size_type i = 0; i < health.healthForms.size(); i++ )
  {
    Image::ImageHealth currentForm = health.healthForms.at(i);
	for ( int j = 0; j < currentForm.getCurrentAmount(); j++)
	{
	  Vector2f position = currentForm.getPosition();
    Vector2f offset = currentForm.getOffset();
	  
	  position.y -= j*offset.y;
	  Vector2f texturePosition = currentForm.getTexturePosition();

	  const GLfloat vertX = position.x;
	  const GLfloat vertY = position.y;
	  const GLfloat vertOffsetX = offset.x;
	  const GLfloat vertOffsetY = offset.y;
    
	  const GLfloat verts[] = {
					vertX, vertY,
					vertX + vertOffsetX, vertY,
					vertX + vertOffsetX, vertY + vertOffsetY,
					vertX, vertY + vertOffsetY
	  };

	  const GLfloat textureX = texturePosition.x / widthTexture;
	  const GLfloat textureY = texturePosition.y / heightTexture;
	  const GLfloat textureWidth = offset.x / widthTexture;
	  const GLfloat textureHeight = offset.y / heightTexture;

	  const GLfloat texVerts[] = {
					textureX, textureY,
					textureX + textureWidth, textureY,
					textureX + textureWidth, textureY + textureHeight,
					textureX, textureY + textureHeight
	  };
            
    glVertexPointer(2, GL_FLOAT, 0, verts);
	  glTexCoordPointer(2, GL_FLOAT, 0, texVerts);
	  glDrawArrays(GL_QUADS, 0, 4);
    }
  }

  glDisableClientState( GL_VERTEX_ARRAY );			
  glDisableClientState( GL_TEXTURE_COORD_ARRAY );	
}

void PlayerStats::Stats::updateFaceState()
{
  int points = health.pointsOfLife;
  int maxPoints = health.maxPointsOfLife;
  int maxFaces = faces.maxFaces;

  for(int i = faces.maxFaces - 1; i >= 0; i--)
  {
	GLfloat maxTopPoints = (GLfloat(i)/GLfloat(maxFaces))*maxPoints;
	GLfloat nextFaceState = ( GLfloat((i + 1))/GLfloat(maxFaces) )*maxPoints;
	if ( points > maxTopPoints && points <= nextFaceState )
	{
	  faces.currentFaceState = i;
	  return;
	}
  }
}

void PlayerStats::Stats::updateHealthBar()
{
  if ( health.pointsOfLife >= 0 )
  {
    health.healthForms.at(0).setCurrentAmount(1);
  }

  health.healthForms.at(1).setCurrentAmount((health.pointsOfLife - 100)/100);

  Vector2f currentPosition= health.healthForms.at(2).getPosition();
  currentPosition.y = 20.0f + health.healthForms.at(1).getOffset().y*(health.healthForms.at(1).getMaxAmount() - 
	                                                                  health.healthForms.at(1).getCurrentAmount());

  health.healthForms.at(2).setPosition(currentPosition.x, currentPosition.y);
}

void PlayerStats::Stats::takeDamage(int damage)
{
  health.pointsOfLife -= damage;
}